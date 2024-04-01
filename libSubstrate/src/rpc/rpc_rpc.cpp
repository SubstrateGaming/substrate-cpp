#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

RpcMethods substrate_client::rpc_methods() const
{
   return rpc<RpcMethods>("rpc_methods");
}

