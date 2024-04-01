#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Option<BlockStats> substrate_client::dev_getBlockStats(Hash at) const
{
   return rpc<Option<BlockStats>>("dev_getBlockStats", at);
}

