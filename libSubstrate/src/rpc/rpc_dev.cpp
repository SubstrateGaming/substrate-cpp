#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Option<BlockStats> substrate_client::dev_getBlockStats(Hash at)
{
   return rpc<Option<BlockStats>>("dev_getBlockStats", at);
}

