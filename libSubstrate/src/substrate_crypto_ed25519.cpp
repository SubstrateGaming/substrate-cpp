#include <substrate/substrate.h>

#include <sodium.h>

class crypto_ed25519 final : public substrate::ICrypto
{
public:
   crypto_ed25519()
   {
   }

   virtual ~crypto_ed25519() override = default;

   virtual key_pair make_keypair(const bytes &seed) const override
   {
      if (seed.size() != crypto_sign_SEEDBYTES)
      {
         throw std::invalid_argument("invalid seed size");
      }

      key_pair result;
      result.public_key.resize(crypto_sign_PUBLICKEYBYTES);
      result.secret_key.resize(crypto_sign_SECRETKEYBYTES);

      // Generate the key pair from the seed
      if (crypto_sign_seed_keypair(result.public_key.data(), result.secret_key.data(), seed.data()) != 0)
      {
         throw std::runtime_error("Failed to generate key pair from seed.");
      }

      return result;
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


substrate::Crypto substrate::make_crypto_ed25519()
{
   // https://doc.libsodium.org/usage
   // sodium_init() returns 0 on success, -1 on failure, and 1 if the library had already been initialized.
   if (sodium_init() == -1)
      return nullptr;

   return std::make_shared<crypto_ed25519>();
}
