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
};

namespace substrate::detail::modules
{
   substrate::modules::State make_module_state(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_state>(logger, socket);
   }
}
