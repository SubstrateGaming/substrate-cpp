#include <substrate/substrate.h>
#include <curl/curl.h>

#include <assert.h>

#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <condition_variable>

#include <nlohmann/json.hpp>

#include "detail/websocket_client.h"

class json_rpc_client : public substrate::detail::websocket_client
{
   using counter_t = uint32_t;

   std::atomic<counter_t> _counter{1};
   std::mutex _mutex;
   std::condition_variable _cv;
   std::unordered_map<counter_t, nlohmann::json> _pending_messages;

public:
   json_rpc_client(const std::string &url)
       : websocket_client(url)
   {
   }

   virtual ~json_rpc_client() override = default;

   std::optional<nlohmann::json> send(const std::string &method, const nlohmann::json &params)
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

private:
   using websocket_client::send;

protected:
   virtual void on_message(std::string message) override final
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
};

//
// client implementation
class client : public substrate::IClient
{
   std::string _url;
   std::unique_ptr<json_rpc_client> _socket;

public:
   client(const std::string &url)
       : _url(url)
   {
   }

   virtual ~client() override
   {
      _socket = nullptr;
   }

   bool connect() override
   {
      assert(_socket == nullptr);
      _socket = std::make_unique<json_rpc_client>(_url);
      if (!_socket->connected())
      {
         _socket = nullptr;
         return false;
      }

      // Start listening
      _socket->start();
      return true;
   }

   bool connected() override { return _socket && _socket->connected(); }

   void wait() override
   {
      assert(_socket != nullptr);
      if (_socket)
      {
         _socket->wait();
      }
   }

   void chain_getBlockHash()
   {
      assert(_socket);

      auto optResponse = _socket->send("chain_getBlockHash", std::vector<uint32_t>({0}));
      if (!optResponse.has_value())
      {
         _socket = nullptr;
      }

      auto value = optResponse.value();
      std::cout << value << std::endl;
   }
};

substrate::Client substrate::make_client(const std::string &url)
{
   return std::make_shared<client>(url);
}