#include <substrate/substrate.h>

substrate::Crypto substrate::make_crypto(substrate::models::KeyType provider)
{
   switch (provider)
   {
   case substrate::models::KeyType::Ed25519:
      return substrate::make_crypto_ed25519();
   case substrate::models::KeyType::Sr25519:
      return substrate::make_crypto_sr25519();
   case substrate::models::KeyType::Ecdsa:
      return substrate::make_crypto_ed25519();
   default:
      break;
   }
   return nullptr;
}

substrate::Crypto substrate::make_crypto_secp256k1()
{
   // Not yet implemented.
   return nullptr;
}

substrate::bytes substrate::get_public_key(const std::string &address)
{
   uint16_t network{0};
   return substrate::get_public_key_with_network(address, network);
}

substrate::bytes substrate::get_public_key_with_network(const std::string &address, uint16_t &network)
{
   network = 42;
   const size_t publicKeyLength = 32;
   substrate::bytes pubkByteList;

   auto bs58decoded = substrate::base58_decode(address);
   auto len = bs58decoded.size();

   substrate::bytes ssPrefixed = {0x53, 0x53, 0x35, 0x38, 0x50, 0x52, 0x45};

   size_t prefixSize;
   // 00000000b..=00111111b (0..=63 inclusive): Simple account/address/network identifier.
   if (len == 35)
   {
      prefixSize = 1;
      // set network
      network = bs58decoded[0];
   }
   // 01000000b..=01111111b (64..=127 inclusive)
   else if (len == 36)
   {
      prefixSize = 2;
      // set network
      uint8_t b2up = static_cast<uint8_t>((bs58decoded[0] << 2) & 0b11111100);
      uint8_t b2lo = static_cast<uint8_t>((bs58decoded[1] >> 6) & 0b00000011);
      uint8_t b2 = b2up | b2lo;
      uint8_t b1 = bs58decoded[1] & 0b00111111;
      network = static_cast<int16_t>((b1 << 8) | b2);
   }
   else
   {
      throw std::runtime_error("unsupported address size");
   }

   pubkByteList.insert(pubkByteList.end(), ssPrefixed.begin(), ssPrefixed.end());
   pubkByteList.insert(pubkByteList.end(), bs58decoded.begin(), bs58decoded.begin() + publicKeyLength + prefixSize);

   auto blake2bHashed = substrate::hash::blake2(pubkByteList, 512);
   if (bs58decoded[publicKeyLength + prefixSize] != blake2bHashed[0] ||
       bs58decoded[publicKeyLength + prefixSize + 1] != blake2bHashed[1])
   {
      throw std::runtime_error("address checksum is wrong");
   }

   return substrate::bytes(bs58decoded.begin() + prefixSize, bs58decoded.begin() + prefixSize + publicKeyLength);
}

std::string substrate::get_address(const substrate::bytes &bytes, uint16_t ss58_prefix)
{
   const size_t sr25519_public_size = 32;
   const size_t public_key_length = 32;
   size_t key_size = 0;

   substrate::bytes plain_addr;
   if (ss58_prefix < 64)
   {
      key_size = 1;
      plain_addr.resize(35);
      plain_addr[0] = static_cast<uint8_t>(ss58_prefix);
      std::copy(bytes.begin(), bytes.end(), plain_addr.begin() + 1);
   }
   else if (ss58_prefix < 16384)
   {
      key_size = 2;
      plain_addr.resize(36);

      auto ident = ss58_prefix & 0b0011111111111111; // clear first two bits
      auto first = static_cast<uint8_t>(((ident & 0b0000000011111100) >> 2) | 0b01000000);
      auto second = static_cast<uint8_t>((ident >> 8) | (ident & 0b0000000000000011) << 6);

      plain_addr[0] = first;
      plain_addr[1] = second;

      std::copy(bytes.begin(), bytes.end(), plain_addr.begin() + 2);
   }
   else
   {
      throw std::runtime_error("unsupported prefix used, support only up to 16383!");
   }

   substrate::bytes ss_prefixed(sr25519_public_size + 7 + key_size);
   substrate::bytes ss_prefixed1 = {0x53, 0x53, 0x35, 0x38, 0x50, 0x52, 0x45};
   std::copy(ss_prefixed1.begin(), ss_prefixed1.end(), ss_prefixed.begin());
   std::copy(plain_addr.begin(), plain_addr.begin() + sr25519_public_size + key_size, ss_prefixed.begin() + 7);

   auto blake2b_hashed = substrate::hash::blake2(ss_prefixed, 512); // Assuming Blake2 hashing function similar to the C# version
   plain_addr[key_size + public_key_length] = blake2b_hashed[0];
   plain_addr[key_size + public_key_length + 1] = blake2b_hashed[1];

   return base58_encode(plain_addr);
}