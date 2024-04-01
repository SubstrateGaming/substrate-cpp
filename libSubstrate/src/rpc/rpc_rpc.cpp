#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

RpcMethods substrate_client::rpc_methods()
{
   return rpc<RpcMethods>("rpc_methods");
}

