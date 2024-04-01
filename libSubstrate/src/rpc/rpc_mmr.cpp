#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

MmrLeafBatchProof substrate_client::mmr_generateProof(Vec<u64> blockNumbers, std::optional<u64> bestKnownBlockNumber, std::optional<BlockHash> at) const
{
   return rpc<MmrLeafBatchProof>("mmr_generateProof", blockNumbers, bestKnownBlockNumber, at);
}

MmrHash substrate_client::mmr_root(std::optional<BlockHash> at) const
{
   return rpc<MmrHash>("mmr_root", at);
}

bool substrate_client::mmr_verifyProof(MmrLeafBatchProof proof) const
{
   return rpc<bool>("mmr_verifyProof", proof);
}

bool substrate_client::mmr_verifyProofStateless(MmrHash root, MmrLeafBatchProof proof) const
{
   return rpc<bool>("mmr_verifyProofStateless", root, proof);
}

