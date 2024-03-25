#include "test_utils.h"

#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

namespace utils
{
   // Function definition
   std::vector<uint8_t> generate_random_bytes(size_t minLength, size_t maxLength)
   {
      // Static to ensure the initialization happens only once
      static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));

      // Define distributions for length and byte values
      std::uniform_int_distribution<size_t> distLength(minLength, maxLength);
      std::uniform_int_distribution<int> distBytes(0, 255);

      // Generate random length within specified range
      size_t messageLength = distLength(rng);

      // Initialize the vector with the determined length
      std::vector<uint8_t> message(messageLength);

      // Fill the vector with random bytes
      for (auto &byte : message)
      {
         byte = static_cast<uint8_t>(distBytes(rng));
      }

      return message;
   }
}
