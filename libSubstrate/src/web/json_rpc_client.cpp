#include "json_rpc_client.h"

#include "logger.h"

using namespace substrate::detail::web;

json_rpc_client::json_rpc_client(substrate::Logger logger, const std::string &url)
    : websocket_client(logger, url)
{
}

nlohmann::json json_rpc_client::send_rpc(const std::string &method, const nlohmann::json &params, substrate::rpc::subscription_callback_t callback)
{
   // generate a unique request id for this rpc call
   const auto request_id = _counter.fetch_add(1u);
   nlohmann::json request = {
       {"jsonrpc", "2.0"},
       {"id", request_id},
       {"method", method},
       {"params", params}};

   // serialize the request to a json string for sending
   const std::string message = request.dump();

   // signal that a response is being awaited.
   // this affects how incoming messages are processed
   {
      std::unique_lock<std::mutex> lock(_mutex);
      _is_processing_one_response = true;
   }

   // attempt to send the message over websocket,
   // setting the flag to false and notifying on failure
   if (!websocket_client::send_message(message))
   {
      std::unique_lock<std::mutex> lock(_mutex);
      _is_processing_one_response = false;
      // ensure waiting threads are not left hanging
      _cv.notify_all();

      throw std::runtime_error(method);
   }

   // wait for the response associated with the request_id
   nlohmann::json response;
   {
      std::unique_lock<std::mutex> lock(_mutex);
      _cv.wait(lock, [&] { return _pending_messages.find(request_id) != _pending_messages.end(); });

      // retrieve the response
      response = _pending_messages[request_id];

      // cleanup by removing the handled response
      _pending_messages.erase(request_id);
   }

   // if a callback is provided, register it
   if (callback)
   {
      // ensuring mutual exclusion while modifying shared state
      std::unique_lock<std::mutex> lock(_mutex);
      assert(response.contains("result"));
      assert(response["result"].is_string());

      // extract subscription id from the response
      const std::string subscription_id{response["result"]};
      assert(!subscription_id.empty());

      // map the subscription id to the callback
      _subscriptions[subscription_id] = callback;
   }

   // after processing, signal that the response has been fully processed
   {
      std::unique_lock<std::mutex> lock(_mutex);
      _is_processing_one_response = false;

      _cv.notify_all();
   }

   return response;
}

std::string json_rpc_client::send(const std::string &method, const nlohmann::json &params)
{
   constexpr auto kResult = "result";

   auto json = send_rpc(method, params);
   assert(json.is_object());
   assert(json.contains(kResult));
   if (json.is_object() && json.contains(kResult))
      return json[kResult];

   throw std::runtime_error(method);
}

nlohmann::json json_rpc_client::send_rpc_result(const std::string &method, const nlohmann::json &params, substrate::rpc::subscription_callback_t callback)
{
   auto response = send_rpc(method, params, callback);
   if (response.contains("result"))
      return response["result"];

   throw std::runtime_error(method);
}

void json_rpc_client::on_message(const std::string &message)
{
   constexpr const char *kId = "id";
   constexpr const char *kSubscription = "subscription";
   constexpr const char *kParams = "params";
   constexpr const char *kResult = "result";

   // attempt to parse the incoming message as json, safely ignoring any exceptions
   constexpr bool allow_exceptions = false;
   auto response = nlohmann::json::parse(message, nullptr, allow_exceptions);
   if (!response.is_object())
   {
      // if the message cannot be parsed into a json object, simply return
      return;
   }

   if (response.contains(kId) || response.contains(kParams))
   {
      if (response.contains(kId) && response[kId].is_number())
      {
         // handle responses to rpc calls identified by an id
         const counter_t id = response[kId].get<counter_t>();
         {
            std::unique_lock<std::mutex> lock(_mutex);

            // store the response
            _pending_messages[id] = response;

            // notify send_rpc that the response has arrived
            _cv.notify_all();

            // wait until send_rpc signals that it has finished processing this response
            _cv.wait(lock, [&] { return !_is_processing_one_response; });
         }
      }
      else if (response.contains(kParams)
         && response[kParams].is_object()
         && response[kParams].contains(kSubscription)
         && response[kParams][kSubscription].is_string()
         && response[kParams].contains(kResult))
      {
         // handle messages tied to a specific subscription
         const std::string subscription_id{response[kParams][kSubscription]};
         substrate::rpc::subscription_callback_t callback;
         {
            std::lock_guard<std::mutex> lock(_mutex);

            // attempt to find the corresponding callback for this subscription
            auto it = _subscriptions.find(subscription_id);
            if (it != _subscriptions.end())
            {
               callback = it->second;
            }
         }

         // if a callback is found, execute it
         if (callback)
         {
            callback(response[kParams][kResult]);
         }
      }
      else
      {
         // log an error if the message doesn't match expected formats
         SLOG_ERROR(kCategory, std::string("message <") + message + std::string("> response format not expected"));
         return;
      }
   }
   else
   {
      // warn if the message is missing crucial identification fields
      SLOG_WARN(kCategory, std::string("message <") + message + std::string("> missing id or subscription"));
      return;
   }
}
