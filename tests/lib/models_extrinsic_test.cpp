#include <gtest/gtest.h>

#include <substrate/substrate.h>

// #/extrinsics/decode/0x03000b88daca6f8e01
// timestamp::set()
TEST(ExtrinsicTest, ExtrinsicDecodeEncodeTest1)
{
   const std::string hex = "0x280403000b88daca6f8e01";

   substrate::decoder decoder(substrate::hex_decode(hex));

   // Decode extrinsic
   substrate::rpc::Extrinsic extrinsic;
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

   // Encode
   substrate::encoder encoder;
   encoder << extrinsic;
   EXPECT_EQ(encoder.assemble_hex(), hex);
}

// balances::transferKeepAlive
TEST(ExtrinsicTest, ExtrinsicDecodeTest2)
{
   const std::string hex = "0x49028400d43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d01003c8a75c61f2939ecd752cf35cca91495fecac095abff8ad904853b26847609fe730d3ed6d8b3d6cd30ca39709bb5a75f893740c14a1b27b08864411007a48b7603040000060300be5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f0b008096b500d3";

   substrate::decoder decoder(substrate::hex_decode(hex));

   // Decode extrinsic
   substrate::rpc::Extrinsic extrinsic;
   decoder >> extrinsic;

   EXPECT_EQ(extrinsic.Signed, true);
   EXPECT_EQ(extrinsic.TransactionVersion, 0x04);
   EXPECT_EQ(extrinsic.Charge.Tip, 0x00);
   EXPECT_EQ(extrinsic.Charge.AssetId, 0x00);

   EXPECT_EQ(extrinsic.Method.ModuleIndex, 0x06);
   EXPECT_EQ(extrinsic.Method.CallIndex, 0x03);
   EXPECT_EQ(decoder.remaining_bytes(), 0);

   // Decode extrinsic's parameters
   substrate::rpc::AccountId dest;
   substrate::CompactInteger value;

   substrate::decoder decoder2(extrinsic.Method.Parameters);
   decoder2 >> dest;
   decoder2 >> value;

   EXPECT_EQ(dest.value(), "0xbe5ddb1579b72e84524fc29e78609e3caf42e85aa118ebfe0b0ad404b5bdd25f");
   EXPECT_EQ(value, 232'000'000'000'000);

   // Encode
   substrate::encoder encoder;
   encoder << extrinsic;
   EXPECT_EQ(encoder.assemble_hex(), hex);
}

TEST(ExtrinsicTest, ExtrinsicDecodeSignedTransaction)
{
   const std::string signed_extrinsic = "0x45028400d43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d015ee8a223bd50126312c7dd4e052cbd596c362e18b576caebf88a46f37f0ae645f8d83b6841c2bcbe7e875de25ab90ffc69cb719ba9f98eb5c66718a47683db8a000800000607008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a480b00a014e33226";

   substrate::decoder decoder(substrate::hex_decode(signed_extrinsic));
   substrate::rpc::Extrinsic extrinsic;
   decoder >> extrinsic;

   substrate::encoder encoder;
   encoder << extrinsic;

   EXPECT_EQ(encoder.assemble(), substrate::hex_decode(signed_extrinsic));


   // // Secret Key URI Alice account:
   // // Secret seed:      0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a
   // // Public key(hex):  0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d
   // // Account ID:       0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d
   // // SS58 Address:     5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY
   // const std::string key = "0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a";
   // auto crypto = substrate::make_crypto_sr25519();
   // const auto key_pair = crypto->make_keypair(substrate::hex_decode(key));

   // EXPECT_EQ(crypto->verify(encoder.assemble(), extrinsic.Signature.Bytes, key_pair.public_key), true);




}
