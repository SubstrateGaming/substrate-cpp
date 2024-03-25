#include "module.h"

using namespace substrate::detail;
using namespace substrate::detail::web;

class module_state : public module, public substrate::modules::IState
{
public:
   module_state(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_state() override = default;

   virtual std::optional<substrate::modules::RuntimeVersion> getRuntimeVersion() const override
   {
      substrate::modules::RuntimeVersion result;

      auto response = _socket->send_rpc_result("state_getRuntimeVersion");
      if (response.has_value())
      {
         const auto json = response.value();
         result.AuthoringVersion = json["authoringVersion"];
         result.ImplVersion = json["implVersion"];
         result.SpecVersion = json["specVersion"];
         result.TransactionVersion = json["transactionVersion"];
         result.ImplName = json["implName"];
         result.SpecName = json["specName"];
         return result;
      }
      return std::nullopt;
   }
};

namespace substrate::detail::modules
{
   substrate::modules::State make_module_state(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_state>(logger, socket);
   }
}
