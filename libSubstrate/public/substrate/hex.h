#pragma once
#include "types.h"

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace substrate
{
   template <typename Container>
   auto hex_encode(const Container &data) -> std::enable_if_t<std::is_same_v<typename Container::value_type, uint8_t>, std::string>
   {
      if (data.empty())
         return std::string();

      std::ostringstream ss;
      ss << "0x";
      std::for_each(std::rbegin(data), std::rend(data), [&](const uint8_t &byte)
                    { ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte); });
      return ss.str();
   }

   static int hex_value(char hex)
   {
      if (hex >= '0' && hex <= '9')
         return hex - '0';
      if (hex >= 'A' && hex <= 'F')
         return hex - 'A' + 10;
      if (hex >= 'a' && hex <= 'f')
         return hex - 'a' + 10;
      throw std::invalid_argument("Invalid hexadecimal character");
   }

   static std::vector<uint8_t> hex_decode(std::string hex)
   {
      if (hex == "0x0")
         return {0x00};

      if (hex.length() % 2 == 1)
         throw std::invalid_argument("The binary key cannot have an odd number of digits");

      if (hex.substr(0, 2) == "0x")
         hex = hex.substr(2);

      if (hex.length() % 2 != 0)
         hex = "0" + hex;

      std::vector<uint8_t> arr(hex.length() / 2);
      for (size_t i = 0; i < hex.length(); i += 2)
         arr[i / 2] = (hex_value(hex[i]) << 4) + hex_value(hex[i + 1]);

      return arr;
   }
}
