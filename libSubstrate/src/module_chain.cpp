#include "module.h"

using namespace substrate::detail;
using namespace substrate::detail::web;

class module_chain : public module, public substrate::modules::IChain
{
public:
   module_chain(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_chain() override = default;
};

namespace substrate::detail::modules
{
   substrate::modules::Chain make_module_chain(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_chain>(logger, socket);
   }
}
