#include "rpc_test.h"

class rpc_author_test : public rpc_test
{
};

TEST_F(rpc_author_test, pendingExtrinsics)
{
   auto pendingExtrinsics = client->author_pendingExtrinsics();
   EXPECT_TRUE(pendingExtrinsics.size() >= 0);
}

TEST_F(rpc_author_test, submitAndWatchExtrinsic)
{
   auto account = substrate::development::make_account_alice();
   substrate::rpc::Method method;
   method.ModuleIndex = 6;
   method.CallIndex = 7;
   method.Parameters = substrate::hex_decode("0x008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a480b00a014e33226");

   const auto extrinsic = client->make_extrinsic(account, method);

   auto subscriptionId = client->author_submitAndWatchExtrinsic([](const nlohmann::json& data) {
      // Should we verify something and actually wait for it?
      // Like a conditional wait?
      EXPECT_FALSE(data.is_null());
   }, extrinsic);

   EXPECT_FALSE(subscriptionId.empty());
}

TEST_F(rpc_author_test, submitExtrinsic)
{
   auto account = substrate::development::make_account_alice();
   substrate::rpc::Method method;
   method.ModuleIndex = 6;
   method.CallIndex = 7;
   method.Parameters = substrate::hex_decode("0x008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a480b00a014e33226");

   const auto extrinsic = client->make_extrinsic(account, method);
   auto id = client->author_submitExtrinsic(extrinsic);

   EXPECT_FALSE(id.const_value().empty());
}
