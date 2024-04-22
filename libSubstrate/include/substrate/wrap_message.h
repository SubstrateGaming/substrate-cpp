#pragma once
#include "types.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT wrap_message
   {
      static const std::string U8A_WRAP_PREFIX_STR;
      static const std::string U8A_WRAP_POSTFIX_STR;
      static substrate::bytes U8A_WRAP_PREFIX;
      static substrate::bytes U8A_WRAP_POSTFIX;
      static size_t wrapLength;

   public:
      [[nodiscard]] static bool is_wrapped(const substrate::bytes& data);
      [[nodiscard]] static bool is_wrapped(const std::string& data);
      [[nodiscard]] static substrate::bytes unwrap(const substrate::bytes& data);
      [[nodiscard]] static substrate::bytes unwrap(const std::string& data);
      [[nodiscard]] static substrate::bytes wrap(const substrate::bytes& data);
      [[nodiscard]] static substrate::bytes wrap(const std::string& data);
   };
}
