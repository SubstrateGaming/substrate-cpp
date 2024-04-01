#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

H256 substrate_client::beefy_getFinalizedHead() const
{
   return rpc<H256>("beefy_getFinalizedHead");
}

BeefyVersionedFinalityProof substrate_client::beefy_subscribeJustifications() const
{
   return rpc<BeefyVersionedFinalityProof>("beefy_subscribeJustifications");
}

