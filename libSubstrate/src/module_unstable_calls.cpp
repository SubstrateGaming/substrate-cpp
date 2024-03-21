#include "module.h"

using namespace substrate::detail;
using namespace substrate::detail::web;

class module_unstable_calls : public module, public substrate::modules::IUnstableCalls
{
public:
   module_unstable_calls(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_unstable_calls() override = default;
};

namespace substrate::detail::modules
{
   substrate::modules::UnstableCalls make_module_unstable_calls(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_unstable_calls>(logger, socket);
   }
}
