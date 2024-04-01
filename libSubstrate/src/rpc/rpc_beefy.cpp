#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

H256 substrate_client::beefy_getFinalizedHead()
{
   return rpc<H256>("beefy_getFinalizedHead");
}

BeefyVersionedFinalityProof substrate_client::beefy_subscribeJustifications()
{
   return rpc<BeefyVersionedFinalityProof>("beefy_subscribeJustifications");
}

