#include <substrate/substrate.h>

extern "C" {
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
      constexpr size_t KeySize = 32;
      static_assert(sizeof(sr25519_mini_secret_key) == KeySize);

      if (seed.size() != KeySize)
      {
         throw std::invalid_argument("invalid seed size");
      }

      sr25519_keypair sr25519_key_pair{0};
      sr25519_mini_secret_key sr25519_key_seed;
      memcpy(&sr25519_key_seed[0], seed.data(), seed.size());
      sr25519_uniform_keypair_from_seed(sr25519_key_pair, sr25519_key_seed);

      key_pair result;
      result.public_key.resize(KeySize);
      result.secret_key.resize(KeySize);
      result.nonce.resize(KeySize);

      memcpy(&result.secret_key[0], &sr25519_key_pair[0], KeySize);
      memcpy(&result.nonce[0], &sr25519_key_pair[32], KeySize);
      memcpy(&result.public_key[0], &sr25519_key_pair[64], KeySize);
      return result;
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

substrate::Crypto substrate::make_crypto_sr25519()
{
   return std::make_shared<crypto_sr25519>();
}
