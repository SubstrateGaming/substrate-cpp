#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Json substrate_client::sync_state_genSyncSpec(bool raw)
{
   return rpc<Json>("sync_state_genSyncSpec", raw);
}

