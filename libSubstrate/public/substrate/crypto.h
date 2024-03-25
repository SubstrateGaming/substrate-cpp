#pragma once
#include "types.h"
#include "models/keytype.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ICrypto
   {
   public:
      virtual ~ICrypto() = default;

      // Syntactic sugar.
      using bytes = std::vector<uint8_t>;

      struct secret_pair
      {
         bytes key;
         bytes nonce; // for sr25519
      };

      struct key_pair
      {
         bytes public_key;
         secret_pair secret;
      };

      [[nodiscard]] virtual key_pair make_keypair(const bytes &seed) const = 0;
      [[nodiscard]] virtual bytes sign(const bytes &message, const key_pair &key_pair) const = 0;
      [[nodiscard]] virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const = 0;
   };

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto(substrate::models::KeyType provider);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_ed25519();
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_sr25519();
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_secp256k1();

   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<uint8_t> get_public_key(const std::string &address);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<uint8_t> get_public_key_with_network(const std::string &address, uint16_t &network);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::string get_address(const std::vector<uint8_t> &bytes, uint16_t ss58_prefix = 42);

}
