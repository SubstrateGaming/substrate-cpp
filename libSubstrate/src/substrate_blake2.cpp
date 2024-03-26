#include <substrate/blake2.h>

extern "C"
{
   // sodium library uses blake2b internally but does not expose it
   // forward declare it and use it
   int blake2b(uint8_t *out, const void *in, const void *key, const uint8_t outlen, const uint64_t inlen, uint8_t keylen);
}

substrate::bytes substrate::blake2(const substrate::bytes &input, size_t size, const substrate::bytes &key)
{
   size_t outlen = size / 8;
   substrate::bytes output(outlen);

   // The key is optional.
   // If not provided, pass nullptr and 0 length to blake2b
   const uint8_t *keyData = key.empty() ? nullptr : key.data();
   size_t keylen = key.size();

   int result = blake2b(output.data(), input.data(), keyData, output.size(), input.size(), keylen);
   if (result != 0)
   {
      throw std::runtime_error("blake2b hashing failed");
   }

   return output;
}
