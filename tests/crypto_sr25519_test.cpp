#include <gtest/gtest.h>
#include <substrate/substrate.h>

#include "test_utils.h"

TEST(CryptoTest, crypto_sr25519_key_pair_test1)
{
   // Secret Key URI Alice account:
   // Secret seed:      0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a
   // Public key(hex):  0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d
   // Account ID:       0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d
   // SS58 Address:     5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY
   const std::string key = "0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a";

   auto crypto = substrate::make_crypto_sr25519();
   const auto key_pair = crypto->make_keypair(substrate::hex_decode(key));

   EXPECT_EQ(key_pair.public_key, substrate::hex_decode("0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d"));
   EXPECT_EQ(key_pair.secret.nonce, substrate::hex_decode("0x925a225d97aa00682d6a59b95b18780c10d7032336e88f3442b42361f4a66011"));
   EXPECT_EQ(substrate::get_address(key_pair.public_key), "5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY");
}

TEST(CryptoTest, crypto_sr25519_key_pair_test2)
{
   // Secret Key URI Bob account:
   // Secret seed:      0x398f0c28f98885e046333d4a41c19cee4c37368a9832c6502f6cfd182e2aef89
   // Public key(hex):  0x8eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48
   // Account ID:       0x8eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48
   // SS58 Address:     5FHneW46xGXgs5mUiveU4sbTyGBzmstUspZC92UhjJM694ty
   const std::string key = "0x398f0c28f98885e046333d4a41c19cee4c37368a9832c6502f6cfd182e2aef89";

   auto crypto = substrate::make_crypto_sr25519();
   const auto key_pair = crypto->make_keypair(substrate::hex_decode(key));

   EXPECT_EQ(key_pair.public_key, substrate::hex_decode("0x8eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48"));
   EXPECT_EQ(key_pair.secret.nonce, substrate::hex_decode("0x41ae88f85d0c1bfc37be41c904e1dfc01de8c8067b0d6d5df25dd1ac0894a325"));
   EXPECT_EQ(substrate::get_address(key_pair.public_key), "5FHneW46xGXgs5mUiveU4sbTyGBzmstUspZC92UhjJM694ty");
}

TEST(CryptoTest, crypto_sr25519_signature_test)
{
   const std::string key = "0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a";

   auto crypto = substrate::make_crypto_sr25519();
   const auto key_pair = crypto->make_keypair(substrate::hex_decode(key));
   const auto message = utils::generate_random_bytes(10, 200);

   // sign the message
   const auto signature = crypto->sign(message, key_pair);

   // verify the signed message
   EXPECT_FALSE(signature.empty());
   EXPECT_EQ(crypto->verify(message, signature, key_pair.public_key), true);
}

TEST(CryptoTest, crypto_sr25519_signature_compare_polkadotjs)
{
   const std::string polkadotJsSignature = "0x5c42ac4e2d55b8e59d9b255af370de03fe177f5545eecbbd784531cb2eb1f2553e0e2b91656f99fae930eb6ff8ac1a3eca4e19d307ecb39832a479a478a8608a";
   const std::string key = "0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a";

   auto crypto = substrate::make_crypto_sr25519();
   const auto key_pair = crypto->make_keypair(substrate::hex_decode("0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a"));

   const std::string message = "I test this signature!";
   const auto message_wrapped = substrate::wrap_message::wrap(message);

   auto signature = crypto->sign(message_wrapped, key_pair);
   EXPECT_FALSE(signature.empty());
   EXPECT_EQ(crypto->verify(message_wrapped, substrate::hex_decode(polkadotJsSignature), key_pair.public_key), true);
}
