#include "json_rpc_client.h"

using namespace substrate::detail;

json_rpc_client::json_rpc_client(const std::string &url)
    : websocket_client(url)
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

   if (!websocket_client::send(request.dump()))
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

void json_rpc_client::on_message(std::string message)
{
   constexpr const char *kId = "id";
   constexpr bool allow_exceptions = false;
   auto response = nlohmann::json::parse(std::move(message), nullptr, allow_exceptions);
   if (!response.is_object())
      return;

   if (!response.contains(kId))
      return; // subscription?

   if (!response[kId].is_number())
      return;

   counter_t id = response[kId];

   std::lock_guard<std::mutex> lock(_mutex);
   _pending_messages[id] = response;
   _cv.notify_all();
}
