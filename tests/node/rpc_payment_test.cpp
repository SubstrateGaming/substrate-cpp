#include "rpc_test.h"

class rpc_payment_test : public rpc_test
{
};

TEST_F(rpc_payment_test, queryFeeDetails)
{
   auto queryFeeDetails1 = client->payment_queryFeeDetails(substrate::rpc::Bytes{substrate::hex_decode("0x280403000b88daca6f8e01")});
   EXPECT_FALSE(queryFeeDetails1.inclusionFee.has_value());

   auto queryFeeDetails2 = client->payment_queryFeeDetails(substrate::rpc::Bytes{substrate::hex_decode("0x49028400d43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d01003c8a75c61f2939ecd752cf35cca91495fecac095abff8ad904853b26847609fe730d3ed6d8b3d6cd30ca39709bb5a75f893740c14a1b27b08864411007a48b7603040000060300be5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f0b008096b500d3")});
   EXPECT_TRUE(queryFeeDetails2.inclusionFee.has_value());

   const auto& queryFeeDetails2Value = queryFeeDetails2.inclusionFee.value();
   EXPECT_TRUE(queryFeeDetails2Value.adjustedWeightFee > 0);
   EXPECT_TRUE(queryFeeDetails2Value.lenFee > 0);
   EXPECT_TRUE(queryFeeDetails2Value.baseFee > 0);
}

TEST_F(rpc_payment_test, queryInfo)
{
   auto queryInfo1 = client->payment_queryInfo(substrate::rpc::Bytes{substrate::hex_decode("0x280403000b88daca6f8e01")});
   EXPECT_EQ(queryInfo1.classz, "mandatory");
   EXPECT_EQ(queryInfo1.partialFee, "0");
   EXPECT_TRUE(queryInfo1.weight.ref_time > 0);
   EXPECT_TRUE(queryInfo1.weight.proof_size > 0);

   auto queryInfo2 = client->payment_queryInfo(substrate::rpc::Bytes{substrate::hex_decode("0x49028400d43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d01003c8a75c61f2939ecd752cf35cca91495fecac095abff8ad904853b26847609fe730d3ed6d8b3d6cd30ca39709bb5a75f893740c14a1b27b08864411007a48b7603040000060300be5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f0b008096b500d3")});
   EXPECT_EQ(queryInfo2.classz, "normal");
   EXPECT_FALSE(queryInfo2.partialFee == "0");
   EXPECT_TRUE(queryInfo2.weight.ref_time > 0);
   EXPECT_TRUE(queryInfo2.weight.proof_size > 0);
}
