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

   virtual ~module_system() override = default;
};

namespace substrate::detail::modules
{
   substrate::modules::System make_module_system(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_system>(logger, socket);
   }
}
