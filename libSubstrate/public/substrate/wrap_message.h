#pragma once
#include "types.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT wrap_message
   {
      static const std::string U8A_WRAP_PREFIX_STR;
      static const std::string U8A_WRAP_POSTFIX_STR;
      static std::vector<uint8_t> U8A_WRAP_PREFIX;
      static std::vector<uint8_t> U8A_WRAP_POSTFIX;
      static size_t wrapLength;

   public:
      [[nodiscard]] static bool is_wrapped(const std::vector<uint8_t>& data);
      [[nodiscard]] static bool is_wrapped(const std::string& data);
      [[nodiscard]] static std::vector<uint8_t> unwrap(const std::vector<uint8_t>& data);
      [[nodiscard]] static std::vector<uint8_t> unwrap(const std::string& data);
      [[nodiscard]] static std::vector<uint8_t> wrap(const std::vector<uint8_t>& data);
      [[nodiscard]] static std::vector<uint8_t> wrap(const std::string& data);
   };
}
