#include "rpc_test.h"

class rpc_system_test : public rpc_test
{
};

TEST_F(rpc_system_test, accountNextIndex)
{
   auto account = substrate::development::make_account_bob();
   auto accountNextIndex = client->system_accountNextIndex(account->get_account_id());
   EXPECT_EQ(accountNextIndex, 0);
}

TEST_F(rpc_system_test, chain)
{
   auto chain = client->system_chain();
   EXPECT_FALSE(chain.empty());
}

TEST_F(rpc_system_test, health)
{
   auto health = client->system_health();
   EXPECT_EQ(health.peers, 0);
   EXPECT_EQ(health.isSyncing, false);
   EXPECT_EQ(health.shouldHavePeers, false);
}

TEST_F(rpc_system_test, localListenAddresses)
{
   auto addresses = client->system_localListenAddresses();
   EXPECT_TRUE(addresses.size() > 0);
   EXPECT_FALSE(addresses[0].empty());
}

TEST_F(rpc_system_test, localPeerId)
{
   auto localPeerId = client->system_localPeerId();
   EXPECT_FALSE(localPeerId.empty());
}

TEST_F(rpc_system_test, name)
{
   auto name = client->system_name();
   EXPECT_FALSE(name.empty());
}

TEST_F(rpc_system_test, nodeRoles)
{
   auto nodeRoles = client->system_nodeRoles();
   EXPECT_FALSE(nodeRoles.empty());
   EXPECT_FALSE(nodeRoles[0].empty());
}

TEST_F(rpc_system_test, properties)
{
   auto properties = client->system_properties();
   EXPECT_TRUE(properties.is_object());
}

TEST_F(rpc_system_test, syncState)
{
   auto syncState = client->system_syncState();
   EXPECT_TRUE(syncState.startingBlock.value() == 0);
   EXPECT_TRUE(syncState.currentBlock.value() > syncState.startingBlock.value());
   EXPECT_TRUE(syncState.highestBlock.has_value() && syncState.highestBlock.value().value() >= syncState.currentBlock.value());
}

TEST_F(rpc_system_test, version)
{
   auto version = client->system_name();
   EXPECT_FALSE(version.empty());
}
