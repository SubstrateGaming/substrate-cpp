#include "module.h"

using namespace substrate::detail;
using namespace substrate::detail::web;

class module_system : public module, public substrate::modules::ISystem
{
public:
   module_system(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   uint32_t getAccountNextIndex(const std::string& ss58_address) const override
   {
      const auto params = json::array({ ss58_address });
      const auto json = _socket->send_rpc_result("system_accountNextIndex", params);
      const uint32_t result = json;
      return result;
   }

   virtual ~module_system() override = default;
};

namespace substrate::detail::modules
{
   substrate::modules::System make_module_system(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_system>(logger, socket);
   }
}
