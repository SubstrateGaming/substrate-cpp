#pragma once
#include "types.h"

#include <span>

namespace substrate
{
   namespace details { class encoder; }

   class LIB_SUBSTRATE_EXPORT encoder
   {
      std::unique_ptr<details::encoder> _detail;

   public:
      encoder();
      virtual ~encoder();

      encoder& operator<<(uint8_t v);
      encoder& operator<<(uint16_t v);
      encoder& operator<<(uint32_t v);
      encoder& operator<<(uint64_t v);

      encoder& operator<<(int8_t v);
      encoder& operator<<(int16_t v);
      encoder& operator<<(int32_t v);
      encoder& operator<<(int64_t v);

      encoder& operator<<(CompactInteger v);
      encoder& operator<<(bool v);

      encoder& operator<<(const std::span<const uint8_t>& v);

      std::vector<uint8_t> assemble() const;
      std::string assemble_hex() const;
   };
}
