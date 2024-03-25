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

   std::optional<uint32_t> getAccountNextIndex(const std::string& ss58_address) const override
   {
      const auto params = json::array({ ss58_address });
      const auto response = _socket->send_rpc_result("system_accountNextIndex", params);
      if (response.has_value())
      {
         const uint32_t result = response.value();
         return result;
      }

      return std::nullopt;
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
