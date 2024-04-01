#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

SignedBlock substrate_client::chain_getBlock(std::optional<BlockHash> hash)
{
   throw std::runtime_error("not implemented");
}

BlockHash substrate_client::chain_getBlockHash(std::optional<BlockNumber> blockNumber)
{
   throw std::runtime_error("not implemented");
}

BlockHash substrate_client::chain_getFinalizedHead()
{
   throw std::runtime_error("not implemented");
}

Header substrate_client::chain_getHeader(std::optional<BlockHash> hash)
{
   throw std::runtime_error("not implemented");
}

Header substrate_client::chain_subscribeAllHeads()
{
   throw std::runtime_error("not implemented");
}

Header substrate_client::chain_subscribeFinalizedHeads()
{
   throw std::runtime_error("not implemented");
}

Header substrate_client::chain_subscribeNewHeads()
{
   throw std::runtime_error("not implemented");
}

