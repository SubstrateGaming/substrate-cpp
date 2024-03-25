#pragma once

#include "logger.h"
#include "web/json_rpc_client.h"

namespace substrate::detail
{
   using namespace substrate::models;
   using json = nlohmann::json;

   class module
   {
   protected:
      substrate::Logger _logger;
      web::json_rpc_client_ptr _socket;

   public:
      module(substrate::Logger logger, web::json_rpc_client_ptr socket);
      virtual ~module() = default;
   };

   Header parse_header(const json& json);
   BlockData parse_block_data(const json& json);
   std::vector<Extrinsic> parse_extrinsics(const json& json);
}
