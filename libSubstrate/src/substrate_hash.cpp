#include <substrate/hash.h>
#include <sodium/crypto_generichash.h>
#include <sodium/crypto_hash_sha256.h>
#include <sodium/crypto_hash_sha512.h>

substrate::bytes substrate::hash::sha256(const substrate::bytes& input)
{
   substrate::bytes output(32);

   int result = crypto_hash_sha256(output.data(), input.data(), input.size());
   if (result != 0)
   {
      throw std::runtime_error("sha256 failed");
   }

   return output;
}

substrate::bytes substrate::hash::sha512(const substrate::bytes& input)
{
   substrate::bytes output(64);

   int result = crypto_hash_sha512(output.data(), input.data(), input.size());
   if (result != 0)
   {
      throw std::runtime_error("sha512 failed");
   }

   return output;
}

substrate::bytes substrate::hash::blake2(const substrate::bytes &input, size_t size, const substrate::bytes &key)
{
   size_t outlen = size / 8;
   substrate::bytes output(outlen);

   // The key is optional.
   // If not provided, pass nullptr and 0 length to blake2b
   const uint8_t *keyData = key.empty() ? nullptr : key.data();
   size_t keylen = key.size();

   // The function crypto_generichash implements blake2b.
   // There is another function crypto_generichash_blake2b but according to the documentation we should call
   // the high-level API.
   //
   // If for some odd reason the "generic" hash implementation changes, our unit-tests should discover that.
   //
   // Source: https://libsodium.gitbook.io/doc/quickstart#should-i-call-crypto_generichash_blake2b-or-just-crypto_generichash
   int result = crypto_generichash(output.data(), output.size(), input.data(), input.size(), keyData, keylen);
   if (result != 0)
   {
      throw std::runtime_error("blake2b hashing failed");
   }

   return output;
}
