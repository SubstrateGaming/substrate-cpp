#include <gtest/gtest.h>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

#include <substrate/substrate.h>

// Function definition
std::vector<uint8_t> generate_random_bytes(size_t minLength, size_t maxLength)
{
   // Static to ensure the initialization happens only once
   static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

   // Define distributions for length and byte values
   std::uniform_int_distribution<size_t> distLength(minLength, maxLength);
   std::uniform_int_distribution<int> distBytes(0, 255);

   // Generate random length within specified range
   size_t messageLength = distLength(rng);

   // Initialize the vector with the determined length
   std::vector<uint8_t> message(messageLength);

   // Fill the vector with random bytes
   for (auto &byte : message)
   {
      byte = static_cast<uint8_t>(distBytes(rng));
   }

   return message;
}

TEST(CryptoTest, crypto_ed25519_signature_test)
{
   const std::string private_key_hex = "0xf5e5767cf153319517630f226876b86c8160cc583bc013744c6bf255f5cc0ee5278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const std::string public_key_hex = "0x278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const auto private_key = substrate::hex_decode(private_key_hex);
   const auto public_key = substrate::hex_decode(public_key_hex);
   const auto message = generate_random_bytes(10, 200);
   auto crypto = substrate::make_crypto_ed25519();

   // sign the message
   const auto signed_message = crypto->sign(message, private_key);

   // verify the signed message
   EXPECT_FALSE(signed_message.empty());
   EXPECT_EQ(crypto->verify(message, signed_message, public_key), true);
}

TEST(CryptoTest, crypto_ed25519_keypair_test1)
{
   const std::string private_key_hex = "0xf5e5767cf153319517630f226876b86c8160cc583bc013744c6bf255f5cc0ee5278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const std::string public_key_hex = "0x278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const auto private_key = substrate::hex_decode(private_key_hex);
   const auto public_key = substrate::hex_decode(public_key_hex);
   auto crypto = substrate::make_crypto_ed25519();

   std::vector<uint8_t> seed(private_key.begin(), private_key.begin() + 32);

   EXPECT_EQ(substrate::hex_encode(seed), "0xf5e5767cf153319517630f226876b86c8160cc583bc013744c6bf255f5cc0ee5");

   auto key_pair = crypto->make_keypair(seed);
   EXPECT_EQ(key_pair.public_key, public_key);
   EXPECT_EQ(key_pair.secret_key, private_key);
}

TEST(CryptoTest, SignatureVerifySignedOnNodeByAccount1)
{
   const std::string public_key_hex = "0x278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const auto public_key = substrate::hex_decode(public_key_hex);
   auto crypto = substrate::make_crypto_ed25519();

   const auto message = substrate::hex_decode("0xA81056D713AF1FF17B599E60D287952E89301B5208324A0529B62DC7369C745D");
   const auto signature = substrate::hex_decode("0x10b6aacb0beca6ca60b712fb5db54e957cec304489366544d96f3e59ac2d4328be7b6602ec98e622c0f16ab427eb497d6ef053e00ddfdb3d3f3b6496b0b17a0c");

   EXPECT_EQ(crypto->verify(message, signature, public_key), true);
}

TEST(CryptoTest, SignatureVerifySignedOnNodeByAccount2)
{
   const std::string private_key_hex = "0xf5e5767cf153319517630f226876b86c8160cc583bc013744c6bf255f5cc0ee5278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const std::string public_key_hex = "0x278117fc144c72340f67d0f2316e8386ceffbf2b2428c9c51fef7c597f1d426e";
   const auto private_key = substrate::hex_decode(private_key_hex);
   const auto public_key = substrate::hex_decode(public_key_hex);
   auto crypto = substrate::make_crypto_ed25519();

   const auto message = substrate::hex_decode("0x0400FF8EAF04151687736326C9FEA17E25FC5287613693C912909CB226AA4794F26A484913DC4F62090B18B6893C1431369461069EE3E9C1DA7F9F9A8C097C0CEBBEAC2BB9");
   const auto signature_original = substrate::hex_decode("0x1c7921583e992bae122ba4a754eb84071ac8a627cc4d050047e3d0dbdaa64718a3728e8f87deb2cb9249527853f85833d1b1c2e3af1c60724c060c1b78670b02");

   const auto signature = crypto->sign(message, private_key);
   EXPECT_EQ(signature, signature_original);
   EXPECT_EQ(crypto->verify(message, signature, public_key), true);
}

TEST(CryptoTest, Ed25519SignatureTestComparePolkadotJs)
{
   const std::string polkadotJsSignature = "0xd2baabb61bcd0026e797136cb0938d55e3c3ea8825c163eb3d1738b3c79af8e8f4953ba4767dc5477202756d3fba97bc50fc3ac8355ff5acfba88a36311f2f0f";
   const std::string rawSeed = "0x70f93a75dbc6ad5b0c051210704a00a9937732d0c360792b0fea24efb8ea8465";

   auto crypto = substrate::make_crypto_ed25519();
   const auto key_pair = crypto->make_keypair(substrate::hex_decode(rawSeed));

   const std::string message = "I test this signature!";
   const auto message_wrapped = substrate::wrap_message::wrap(message);

   auto signature = crypto->sign(message_wrapped, key_pair.secret_key);
   EXPECT_EQ(signature, substrate::hex_decode(polkadotJsSignature));
}
