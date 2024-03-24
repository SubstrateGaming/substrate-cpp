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

      [[nodiscard]] virtual std::pair<bytes, bytes> make_keypair(const bytes& seed) const = 0;
      [[nodiscard]] virtual bytes sign(const bytes &message, const bytes &private_key) const = 0;
      [[nodiscard]] virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const = 0;
   };

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto(substrate::models::KeyType provider);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_ed25519();
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_sr25519();
   [[nodiscard]] LIB_SUBSTRATE_EXPORT Crypto make_crypto_secp256k1();
}
