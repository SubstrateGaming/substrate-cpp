#include <substrate/hex.h>

namespace
{
   int hex_value(char hex)
   {
      if (hex >= '0' && hex <= '9')
         return hex - '0';
      if (hex >= 'A' && hex <= 'F')
         return hex - 'A' + 10;
      if (hex >= 'a' && hex <= 'f')
         return hex - 'a' + 10;
      throw std::invalid_argument("invalid hexadecimal character");
   }
}

std::string substrate::hex_encode(const substrate::bytes &input)
{
   if (input.empty())
      return std::string();

   std::ostringstream ss;
   ss << "0x";
   std::for_each(std::begin(input), std::end(input), [&](const uint8_t &byte)
                 { ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte); });
   return ss.str();
}

substrate::bytes substrate::hex_decode(std::string input)
{
   if (input == "0x0")
      return {0x00};

   if (input.length() % 2 == 1)
      throw std::invalid_argument("The binary key cannot have an odd number of digits");

   if (input.substr(0, 2) == "0x")
      input = input.substr(2);

   if (input.length() % 2 != 0)
      input = "0" + input;

   substrate::bytes arr(input.length() / 2);
   for (size_t i = 0; i < input.length(); i += 2)
      arr[i / 2] = (hex_value(input[i]) << 4) + hex_value(input[i + 1]);

   return arr;
}
