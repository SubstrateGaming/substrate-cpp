#pragma once
#include "types.h"

#include <span>

namespace substrate
{
   namespace details { class decoder; }

   class LIB_SUBSTRATE_EXPORT decoder
   {
      std::unique_ptr<details::decoder> _detail;

   public:
      decoder(substrate::bytes bytes);
      virtual ~decoder();

      size_t size() const;
      size_t remaining_bytes() const;
      std::span<const uint8_t> bytes() const;
      void seek(size_t offset);

      decoder& operator>>(uint8_t& v);
      decoder& operator>>(uint16_t& v);
      decoder& operator>>(uint32_t& v);
      decoder& operator>>(uint64_t& v);

      decoder& operator>>(int8_t& v);
      decoder& operator>>(int16_t& v);
      decoder& operator>>(int32_t& v);
      decoder& operator>>(int64_t& v);

      decoder& operator>>(CompactInteger& v);
      decoder& operator>>(bool& v);

      // Handled as static collection, not dynamic.
      decoder& operator>>(substrate::bytes& v);
   };
}
