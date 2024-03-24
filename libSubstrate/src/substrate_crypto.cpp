#include <substrate/substrate.h>

#include <sodium.h>

class crypto_ed25519 final : public substrate::ICrypto
{
public:
   crypto_ed25519()
   {
   }

   virtual ~crypto_ed25519() override = default;

   virtual std::pair<bytes, bytes> make_keypair(const bytes &seed) const override
   {
      if (seed.size() != crypto_sign_SEEDBYTES)
      {
         throw std::invalid_argument("invalid seed size");
      }

      bytes public_key(crypto_sign_PUBLICKEYBYTES);
      bytes private_key(crypto_sign_SECRETKEYBYTES);

      // Generate the key pair from the seed
      if (crypto_sign_seed_keypair(public_key.data(), private_key.data(), seed.data()) != 0)
      {
         throw std::runtime_error("Failed to generate key pair from seed.");
      }

      return {public_key, private_key};
   }

   virtual bytes sign(const bytes &message, const bytes &private_key) const override
   {
      if (private_key.size() != crypto_sign_SECRETKEYBYTES)
      {
         throw std::invalid_argument("invalid private key size");
      }

      bytes signature(crypto_sign_BYTES);
      unsigned long long signature_len{0ull};

      // use crypto_sign_detached to generate the signature
      if (crypto_sign_detached(signature.data(), &signature_len, message.data(), message.size(), private_key.data()) != 0)
      {
         throw std::runtime_error("failed to sign the message");
      }

      signature.resize(signature_len);
      return signature;
   }

   virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const override
   {
      // ensure that the provided public key is the correct size
      if (public_key.size() != crypto_sign_PUBLICKEYBYTES)
      {
         throw std::invalid_argument("invalid public key size");
      }

      // ensure that the provided signature is the correct size
      if (signature.size() != crypto_sign_BYTES)
      {
         throw std::invalid_argument("invalid signature size");
      }

      // perform the signature verification
      int result = crypto_sign_verify_detached(signature.data(), message.data(), message.size(), public_key.data());

      // crypto_sign_verify_detached returns 0 on success
      return result == 0;
   }
};

class crypto_sr25519 final : public substrate::ICrypto
{
public:
   crypto_sr25519()
   {
   }

   virtual ~crypto_sr25519() override = default;

   virtual std::pair<bytes, bytes> make_keypair(const bytes &seed) const override
   {
      return {};
   }

   virtual bytes sign(const bytes &message, const bytes &private_key) const override
   {
      return bytes{};
   }

   virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const override
   {
      return false;
   }
};

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

substrate::Crypto substrate::make_crypto_ed25519()
{
   // https://doc.libsodium.org/usage
   // sodium_init() returns 0 on success, -1 on failure, and 1 if the library had already been initialized.
   if (sodium_init() == -1)
      return nullptr;

   return std::make_shared<crypto_ed25519>();
}

substrate::Crypto substrate::make_crypto_sr25519()
{
   return std::make_shared<crypto_sr25519>();
}

substrate::Crypto substrate::make_crypto_secp256k1()
{
   // Not yet implemented.
   return nullptr;
}

std::vector<uint8_t> substrate::get_public_key(const std::string &address)
{
   uint16_t network{0};
   return substrate::get_public_key_with_network(address, network);
}

std::vector<uint8_t> substrate::get_public_key_with_network(const std::string &address, uint16_t &network)
{
   network = 42;
   const size_t publicKeyLength = 32;
   std::vector<uint8_t> pubkByteList;

   auto bs58decoded = substrate::base58_decode(address);
   auto len = bs58decoded.size();

   std::vector<uint8_t> ssPrefixed = {0x53, 0x53, 0x35, 0x38, 0x50, 0x52, 0x45};

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

   auto blake2bHashed = substrate::blake2(pubkByteList, 512);
   if (bs58decoded[publicKeyLength + prefixSize] != blake2bHashed[0] ||
       bs58decoded[publicKeyLength + prefixSize + 1] != blake2bHashed[1])
   {
      throw std::runtime_error("address checksum is wrong");
   }

   return std::vector<uint8_t>(bs58decoded.begin() + prefixSize, bs58decoded.begin() + prefixSize + publicKeyLength);
}