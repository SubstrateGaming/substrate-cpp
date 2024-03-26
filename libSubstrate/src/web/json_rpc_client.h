#pragma once

#include "websocket_client.h"

#include <nlohmann/json.hpp>

namespace substrate::detail::web
{
   class json_rpc_client : public websocket_client
   {
      constexpr static auto kCategory = "json_rpc_client";
      using counter_t = uint32_t;

      std::atomic<counter_t> _counter{1};
      std::mutex _mutex;
      std::condition_variable _cv;
      std::unordered_map<counter_t, nlohmann::json> _pending_messages;

   public:
      json_rpc_client(substrate::Logger logger, const std::string &url);
      virtual ~json_rpc_client() override = default;

      std::string send(const std::string &method, const nlohmann::json &params = nullptr);
      nlohmann::json send_rpc(const std::string &method, const nlohmann::json &params = nullptr);
      nlohmann::json send_rpc_result(const std::string &method, const nlohmann::json &params = nullptr);

   protected:
      virtual void on_message(const std::string& message) override final;
   };

   using json_rpc_client_ptr = std::shared_ptr<json_rpc_client>;
}
