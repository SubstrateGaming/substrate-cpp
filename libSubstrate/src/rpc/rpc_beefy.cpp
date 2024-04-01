#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

H256 substrate_client::beefy_getFinalizedHead()
{
   throw std::runtime_error("not implemented");
}

BeefyVersionedFinalityProof substrate_client::beefy_subscribeJustifications()
{
   throw std::runtime_error("not implemented");
}

