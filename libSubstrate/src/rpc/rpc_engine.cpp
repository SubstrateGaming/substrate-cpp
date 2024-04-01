#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

CreatedBlock substrate_client::engine_createBlock(bool createEmpty, bool finalize, std::optional<BlockHash> parentHash) const
{
   return rpc<CreatedBlock>("engine_createBlock", createEmpty, finalize, parentHash);
}

bool substrate_client::engine_finalizeBlock(BlockHash hash, std::optional<Justification> justification) const
{
   return rpc<bool>("engine_finalizeBlock", hash, justification);
}

