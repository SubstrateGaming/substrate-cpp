#include <gtest/gtest.h>

#include <substrate/substrate.h>

// #/extrinsics/decode/0x03000b88daca6f8e01
// timestamp::set()
TEST(ExtrinsicTest, ExtrinsicDecodeTest1)
{
   // timestamp::set()
   const std::string hex = "0x280403000b88daca6f8e01";

   substrate::decoder decoder(substrate::hex_decode(hex));

   // Decode extrinsic
   substrate::models::Extrinsic extrinsic;
   decoder >> extrinsic;

   EXPECT_EQ(extrinsic.Signed, false);
   EXPECT_EQ(extrinsic.TransactionVersion, 0x04);
   EXPECT_EQ(extrinsic.Method.ModuleIndex, 0x03);
   EXPECT_EQ(extrinsic.Method.CallIndex, 0x00);
   EXPECT_EQ(decoder.remaining_bytes(), 0);

   // Decode extrinsic's parameters
   substrate::CompactInteger timestamp;
   substrate::decoder decoder2(extrinsic.Method.Parameters);
   decoder2 >> timestamp;
   EXPECT_EQ(timestamp, 1'711'272'549'000);

}

// balances::transferKeepAlive
TEST(ExtrinsicTest, ExtrinsicDecodeTest2)
{
   const std::string hex = "0x49028400d43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d01003c8a75c61f2939ecd752cf35cca91495fecac095abff8ad904853b26847609fe730d3ed6d8b3d6cd30ca39709bb5a75f893740c14a1b27b08864411007a48b7603040000060300be5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f0b008096b500d3";

   substrate::decoder decoder(substrate::hex_decode(hex));

   // Decode extrinsic
   substrate::models::Extrinsic extrinsic;
   decoder >> extrinsic;

   EXPECT_EQ(extrinsic.Signed, true);
   EXPECT_EQ(extrinsic.TransactionVersion, 0x04);
   EXPECT_EQ(extrinsic.Charge.Tip, 0x00);
   EXPECT_EQ(extrinsic.Charge.AssetId, 0x00);

   EXPECT_EQ(extrinsic.Method.ModuleIndex, 0x06);
   EXPECT_EQ(extrinsic.Method.CallIndex, 0x03);
   EXPECT_EQ(decoder.remaining_bytes(), 0);

   // Decode extrinsic's parameters
   substrate::models::AccountId32 dest;
   substrate::CompactInteger value;

   substrate::decoder decoder2(extrinsic.Method.Parameters);
   decoder2 >> dest;
   decoder2 >> value;

   EXPECT_EQ(dest.value(), "0xbe5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f");
   EXPECT_EQ(value, 232'000'000'000'000);

}