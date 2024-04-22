#include <substrate/base58.h>
#include <assert.h>

// https://github.com/bitcoin/bitcoin/blob/master/src/base58.cpp
// Copyright (c) 2014-2022 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/** All alphanumeric characters except for "0", "I", "O", and "l" */
static const char *pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
static const int8_t mapBase58[256] = {
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
    -1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
    22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
    -1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
    47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
    -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
};

// Modified from Bitcoin implementation.
std::string substrate::base58_encode(substrate::bytes input)
{
   // Skip & count leading zeroes.
   int zeroes = 0;
   while (!input.empty() && input.front() == 0)
   {
      input.erase(input.begin());
      zeroes++;
   }
   // Allocate enough space in big-endian base58 representation.
   int size = input.size() * 138 / 100 + 1; // log(256) / log(58), rounded up.
   std::vector<unsigned char> b58(size);
   // Process the bytes.
   while (!input.empty())
   {
      int carry = input.front();
      input.erase(input.begin());
      int i = 0;
      // Apply "b58 = b58 * 256 + ch".
      for (auto it = b58.rbegin(); (carry != 0 || i < size) && (it != b58.rend()); ++it, ++i)
      {
         carry += 256 * (*it);
         *it = carry % 58;
         carry /= 58;
      }
      assert(carry == 0);
   }
   // Skip leading zeroes in base58 result.
   auto it = std::find_if(b58.begin(), b58.end(), [](unsigned char c)
                          { return c != 0; });
   // Translate the result into a string.
   std::string str;
   str.reserve(zeroes + std::distance(it, b58.end()));
   str.assign(zeroes, '1'); // Add '1' for each leading zero
   while (it != b58.end())
   {
      str += pszBase58[*(it++)];
   }
   return str;
}

// Modified from Bitcoin implementation.
substrate::bytes substrate::base58_decode(const std::string &input)
{
   const char *psz = input.c_str();

   int zeroes = 0;
   int length = 0;
   while (*psz == '1')
   {
      zeroes++;
      psz++;
   }

   // Allocate enough space in big-endian base256 representation
   int size = strlen(psz) * 733 / 1000 + 1; // log(58) / log(256), rounded up
   substrate::bytes b256(size);

   // guarantee not out of range
   static_assert(std::size(mapBase58) == 256, "mapBase58.size() should be 256");

   while (*psz)
   {
      int carry = mapBase58[static_cast<uint8_t>(*psz)];
      if (carry == -1)
      {
         // Invalid b58 character
         throw std::invalid_argument("invalid base58 character");
      }

      for (auto it = b256.rbegin(); it != b256.rend(); ++it)
      {
         carry += 58 * (*it);
         *it = carry % 256;
         carry /= 256;

         // Instead of checking carry == 0 to break early, ensure that we only
         // process digits that have been affected by previous iterations (i.e., limit by 'length').
         if (it - b256.rbegin() >= length)
         {
            break;
         }
      }
      assert(carry == 0);
      length++;
      psz++;
   }

   if (*psz != 0)
   {
      throw std::invalid_argument("invalid base58 string");
   }

   // Skip leading zeroes in b256
   auto it = std::find_if(b256.begin(), b256.end(), [](uint8_t byte)
                          { return byte != 0; });

   substrate::bytes result;
   result.reserve(zeroes + (b256.end() - it));
   result.assign(zeroes, 0x00); // Add zeroes represented by leading '1's
   result.insert(result.end(), it, b256.end());
   return result;
}
