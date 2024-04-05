#pragma once
#include "types.h"
#include "rpc_types.h"

namespace substrate
{
   // TODO: Introduce crypto namespace?
   class LIB_SUBSTRATE_EXPORT ICrypto
   {
   public:
      virtual ~ICrypto() = default;

      // TODO: Move
      struct secret_pair
      {
         bytes key;
         bytes nonce; // for sr25519
      };

      // TODO: Move
      struct key_pair
      {
         bytes public_key;
         secret_pair secret;
      };

      [[nodiscard]] virtual key_pair make_keypair(const bytes &seed) const = 0;
      [[nodiscard]] virtual bytes sign(const bytes &message, const key_pair &key_pair) const = 0;
      [[nodiscard]] virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const = 0;
   };

   LIB_SUBSTRATE_EXPORT [[nodiscard]] Crypto make_crypto(substrate::rpc::KeyType provider);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] Crypto make_crypto_ed25519();
   LIB_SUBSTRATE_EXPORT [[nodiscard]] Crypto make_crypto_sr25519();
   LIB_SUBSTRATE_EXPORT [[nodiscard]] Crypto make_crypto_secp256k1();
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes pbkdf2_hmac_sha512(uint32_t derived_key_length, const substrate::bytes& password, const substrate::bytes& salt, uint32_t iteration_count);

   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes get_public_key(const std::string &address);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes get_public_key_with_network(const std::string &address, uint16_t &network);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] std::string get_address(const substrate::bytes &bytes, uint16_t ss58_prefix = 42);

}
