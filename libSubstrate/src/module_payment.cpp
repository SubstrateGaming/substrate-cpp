#include "module.h"

using namespace substrate::detail;
using namespace substrate::detail::web;

class module_payment : public module, public substrate::modules::IPayment
{
public:
   module_payment(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_payment() override = default;
};

namespace substrate::detail::modules
{
   substrate::modules::Payment make_module_payment(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_payment>(logger, socket);
   }
}
