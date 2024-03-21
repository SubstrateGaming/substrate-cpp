#include "json_rpc_client.h"

#include "logger.h"

using namespace substrate::detail;

json_rpc_client::json_rpc_client(substrate::Logger logger, const std::string &url)
    : websocket_client(logger, url)
{
}

std::optional<nlohmann::json> json_rpc_client::send(const std::string &method, const nlohmann::json &params)
{
   const auto request_id = _counter.fetch_add(1u);
   nlohmann::json request = {
       {"jsonrpc", "2.0"},
       {"id", request_id},
       {"method", method},
       {"params", params}};

   const std::string message = request.dump();
   SLOG_DEBUG(kCategory, std::format("send rpc {} as json {}", method, message));

   if (!websocket_client::send(message))
      return std::nullopt;

   // Wait for the response
   std::unique_lock<std::mutex> lock(_mutex);
   _cv.wait(lock, [&]
            { return _pending_messages.find(request_id) != _pending_messages.end(); });

   // Retrieve the response
   nlohmann::json response = _pending_messages[request_id];
   _pending_messages.erase(request_id);
   return response;
}

void json_rpc_client::on_message(const std::string& message)
{
   SLOG_DEBUG(kCategory, std::format("recv message as json {}", message));

   constexpr const char *kId = "id";
   constexpr bool allow_exceptions = false;
   auto response = nlohmann::json::parse(message, nullptr, allow_exceptions);
   if (!response.is_object())
      return;

   if (!response.contains(kId))
   {
      SLOG_WARN(kCategory, std::format("message <{}> missing id, a subscription?", message));
      return;
   }

   if (!response[kId].is_number())
   {
      SLOG_ERROR(kCategory, std::format("message <{}> missing number based id, got id={}", message, response[kId].dump()));
      return;
   }

   counter_t id = response[kId];
   std::lock_guard<std::mutex> lock(_mutex);
   _pending_messages[id] = response;
   _cv.notify_all();
}
