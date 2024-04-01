#include "rpc_test.h"

class rpc_chain_test : public rpc_test
{
};

TEST_F(rpc_chain_test, getBlock)
{
   auto result = client->chain_getBlock();
   EXPECT_FALSE(result.Block.Extrinsics.empty());
   EXPECT_FALSE(result.Justifications.has_value());
}

TEST_F(rpc_chain_test, getBlockHash)
{
   auto result = client->chain_getBlockHash();
   EXPECT_FALSE(result.const_value().empty());
}

TEST_F(rpc_chain_test, getFinalizedHead)
{
   auto result = client->chain_getFinalizedHead();
   EXPECT_FALSE(result.const_value().empty());
}

TEST_F(rpc_chain_test, getHeader)
{
   auto result = client->chain_getHeader();
   EXPECT_TRUE(result.number > 0);
   EXPECT_FALSE(result.parentHash.const_value().empty());
   EXPECT_FALSE(result.stateRoot.const_value().empty());
   EXPECT_FALSE(result.extrinsicsRoot.const_value().empty());
   EXPECT_FALSE(result.digest.Logs.empty());
}

TEST_F(rpc_chain_test, subscribeAllHeads)
{
   // TODO: Implement subscribe
   // auto result = client->chain_subscribeAllHeads();
}

TEST_F(rpc_chain_test, subscribeFinalizedHeads)
{
   // TODO: Implement subscribe
   // auto result = client->chain_subscribeFinalizedHeads();
}

TEST_F(rpc_chain_test, subscribeNewHeads)
{
   // TODO: Implement subscribe
   // auto result = client->chain_subscribeNewHeads();
}
