#pragma once

#include "logger.h"
#include "web/json_rpc_client.h"

namespace substrate::detail
{
   class module
   {
   protected:
      substrate::Logger _logger;
      web::json_rpc_client_ptr _socket;

   public:
      module(substrate::Logger logger, web::json_rpc_client_ptr socket);
      virtual ~module() = default;
   };
}
