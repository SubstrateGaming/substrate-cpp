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

   // create provider
   auto crypto = substrate::make_crypto_ed25519();
   EXPECT_TRUE(crypto != nullptr);

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

   std::vector<uint8_t> seed(private_key.begin(), private_key.begin() + 32);

   // create provider
   auto crypto = substrate::make_crypto_ed25519();
   EXPECT_TRUE(crypto != nullptr);

   EXPECT_EQ(substrate::hex_encode(seed), "0xf5e5767cf153319517630f226876b86c8160cc583bc013744c6bf255f5cc0ee5");

   auto pair = crypto->make_keypair(seed);
   EXPECT_EQ(pair.first, public_key);
   EXPECT_EQ(pair.second, private_key);

}
