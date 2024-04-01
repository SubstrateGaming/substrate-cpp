#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

MmrLeafBatchProof substrate_client::mmr_generateProof(Vec<u64> blockNumbers, std::optional<u64> bestKnownBlockNumber, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

MmrHash substrate_client::mmr_root(std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::mmr_verifyProof(MmrLeafBatchProof proof)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::mmr_verifyProofStateless(MmrHash root, MmrLeafBatchProof proof)
{
   throw std::runtime_error("not implemented");
}

