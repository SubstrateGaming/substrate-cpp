#include <substrate/substrate.h>

extern "C"
{
#include <sr25519-donna.h>
}

class crypto_sr25519 final : public substrate::ICrypto
{
public:
   crypto_sr25519()
   {
   }

   virtual ~crypto_sr25519() override = default;

   virtual key_pair make_keypair(const bytes &seed) const override
   {
      if (seed.size() != sizeof(sr25519_mini_secret_key))
         throw std::invalid_argument("invalid seed size");

      sr25519_keypair sr25519_key_pair{0};
      sr25519_mini_secret_key sr25519_key_seed;
      memcpy(&sr25519_key_seed[0], seed.data(), seed.size());
      sr25519_keypair_from_seed(sr25519_key_pair, sr25519_key_seed);

      key_pair result;
      result.public_key.resize(sizeof(sr25519_public_key));
      result.secret.key.resize(sizeof(sr25519_secret_key_key));
      result.secret.nonce.resize(sizeof(sr25519_secret_key_nonce));

      memcpy(&result.secret.key[0], &sr25519_key_pair[0], sizeof(sr25519_secret_key_key));
      memcpy(&result.secret.nonce[0], &sr25519_key_pair[sizeof(sr25519_secret_key_key)], sizeof(sr25519_secret_key_nonce));
      memcpy(&result.public_key[0], &sr25519_key_pair[sizeof(sr25519_secret_key_key) + sizeof(sr25519_secret_key_nonce)], sizeof(sr25519_public_key));
      return result;
   }

   virtual bytes sign(const bytes &message, const key_pair &key_pair) const override
   {
      if (key_pair.public_key.size() != sizeof(sr25519_public_key))
         throw std::invalid_argument("invalid public key size");

      if (key_pair.secret.key.size() != sizeof(sr25519_secret_key_key))
         throw std::invalid_argument("invalid secret key size");

      if (key_pair.secret.nonce.size() != sizeof(sr25519_secret_key_nonce))
         throw std::invalid_argument("invalid nonce size");

      sr25519_public_key public_key{0};
      memcpy(&public_key[0], key_pair.public_key.data(), key_pair.public_key.size());

      sr25519_secret_key secret{0};
      memcpy(&secret[0], key_pair.secret.key.data(), sizeof(sr25519_secret_key_key));
      memcpy(&secret[sizeof(sr25519_secret_key_key)], key_pair.secret.nonce.data(), sizeof(sr25519_secret_key_nonce));

      sr25519_signature signature{0};
      sr25519_sign(signature, public_key, secret, message.data(), message.size());

      bytes result(sizeof(sr25519_signature));
      memcpy(result.data(), &signature[0], sizeof(sr25519_signature));
      return result;
   }

   virtual bool verify(const bytes &message, const bytes &signature, const bytes &public_key) const override
   {
      if (signature.size() != sizeof(sr25519_signature))
         throw std::invalid_argument("invalid signature size");

      if (public_key.size() != sizeof(sr25519_public_key))
         throw std::invalid_argument("invalid public key size");

      sr25519_signature sr25519_signature{0};
      memcpy(&sr25519_signature[0], signature.data(), sizeof(sr25519_signature));

      sr25519_public_key sr25519_public_key{0};
      memcpy(&sr25519_public_key[0], public_key.data(), sizeof(sr25519_public_key));

      return sr25519_verify(sr25519_signature, message.data(), message.size(), sr25519_public_key);
   }
};

substrate::Crypto substrate::make_crypto_sr25519()
{
   return std::make_shared<crypto_sr25519>();
}
