#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

SignedBlock substrate_client::chain_getBlock(std::optional<BlockHash> hash)
{
   return rpc<SignedBlock>("chain_getBlock", hash);
}

BlockHash substrate_client::chain_getBlockHash(std::optional<BlockNumber> blockNumber)
{
   return rpc<BlockHash>("chain_getBlockHash", blockNumber);
}

BlockHash substrate_client::chain_getFinalizedHead()
{
   return rpc<BlockHash>("chain_getFinalizedHead");
}

Header substrate_client::chain_getHeader(std::optional<BlockHash> hash)
{
   return rpc<Header>("chain_getHeader", hash);
}

Header substrate_client::chain_subscribeAllHeads()
{
   return rpc<Header>("chain_subscribeAllHeads");
}

Header substrate_client::chain_subscribeFinalizedHeads()
{
   return rpc<Header>("chain_subscribeFinalizedHeads");
}

Header substrate_client::chain_subscribeNewHeads()
{
   return rpc<Header>("chain_subscribeNewHeads");
}

