#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

CreatedBlock substrate_client::engine_createBlock(bool createEmpty, bool finalize, std::optional<BlockHash> parentHash)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::engine_finalizeBlock(BlockHash hash, std::optional<Justification> justification)
{
   throw std::runtime_error("not implemented");
}

