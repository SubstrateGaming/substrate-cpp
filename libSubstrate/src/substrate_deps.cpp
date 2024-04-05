#include <substrate/substrate.h>

#include <sodium.h>

std::vector<uint8_t> substrate::utils::make_random_bytes(size_t size)
{
   // https://doc.libsodium.org/usage
   // sodium_init() returns 0 on success, -1 on failure, and 1 if the library had already been initialized.
   if (sodium_init() == -1)
      throw std::runtime_error("sodium not initialized");

   std::vector<uint8_t> result(size);
   randombytes_buf(result.data(), size);
   return result;
}
