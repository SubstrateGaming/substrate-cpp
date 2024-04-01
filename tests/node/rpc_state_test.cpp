#include "rpc_test.h"

class rpc_state_test : public rpc_test
{
public:
   substrate::rpc::StorageKey _testKey;

protected:
   virtual void SetUp() override
   {
      __super::SetUp();

      _testKey = client->state_getKeysPaged(substrate::rpc::StorageKey("0x"), 1).at(0);
   }
};

TEST_F(rpc_state_test, call)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getChildKeys)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getChildReadProof)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getChildStorage)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getChildStorageHash)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getChildStorageSize)
{
   // Not sure how to test that.
   // All types are used in this call are tested, though.
}

TEST_F(rpc_state_test, getKeys)
{
   auto keys = client->state_getKeys(substrate::rpc::StorageKey{"0x"});
   EXPECT_FALSE(keys.empty());
}

TEST_F(rpc_state_test, getKeysPaged)
{
   auto keys = client->state_getKeysPaged(substrate::rpc::StorageKey{"0x"}, 10);
   EXPECT_EQ(keys.size(), 10);
}

TEST_F(rpc_state_test, getMetadata)
{
   auto metadata = client->state_getMetadata();
   EXPECT_FALSE(metadata.empty());
}

TEST_F(rpc_state_test, getReadProof)
{
   auto readProof = client->state_getReadProof({_testKey});
   EXPECT_FALSE(readProof.at.const_value().empty());
   EXPECT_FALSE(readProof.proof.empty());
}

TEST_F(rpc_state_test, getRuntimeVersion)
{
   auto runtime_version = client->state_getRuntimeVersion();
   const auto r = client->getRuntimeVersion();
   EXPECT_EQ(r.authoringVersion, runtime_version.authoringVersion);
   EXPECT_EQ(r.implName, runtime_version.implName);
   EXPECT_EQ(r.implVersion, runtime_version.implVersion);
   EXPECT_EQ(r.specName, runtime_version.specName);
   EXPECT_EQ(r.specVersion, runtime_version.specVersion);
   EXPECT_EQ(r.transactionVersion, runtime_version.transactionVersion);
   EXPECT_FALSE(r.specName.empty());
}

TEST_F(rpc_state_test, getStorage)
{
   auto storage = client->state_getStorage(_testKey);
   EXPECT_FALSE(storage.value().empty());
}

TEST_F(rpc_state_test, getStorageHash)
{
   auto hash = client->state_getStorageHash(this->_testKey);
   EXPECT_FALSE(hash.const_value().empty());
}

TEST_F(rpc_state_test, getStorageSize)
{
   auto size = client->state_getStorageSize(this->_testKey);
   EXPECT_TRUE(size > 0);
}

TEST_F(rpc_state_test, queryStorageAt)
{
   auto keys = client->state_getKeysPaged(substrate::rpc::StorageKey("0x"), 10);
   auto queried = client->state_queryStorageAt(keys);
   EXPECT_FALSE(queried.empty());
}

TEST_F(rpc_state_test, subscribeRuntimeVersion)
{
   auto subscriptionId = client->state_subscribeRuntimeVersion([](const nlohmann::json&) {});
   EXPECT_FALSE(subscriptionId.empty());
}

TEST_F(rpc_state_test, subscribeStorage)
{
   auto subscriptionId = client->state_subscribeStorage([](const nlohmann::json&) {});
   EXPECT_FALSE(subscriptionId.empty());
}
