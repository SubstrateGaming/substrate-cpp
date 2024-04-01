#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Json substrate_client::sync_state_genSyncSpec(bool raw) const
{
   return rpc<Json>("sync_state_genSyncSpec", raw);
}

