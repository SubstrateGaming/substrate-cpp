#pragma once
#include "../types.h"

namespace substrate::models
{
   struct Era
   {
      bool IsImmortal{false};
      uint64_t Period{0};
      uint64_t Phase{0};

      uint64_t get_start(uint64_t blockNumber) const;
      static Era make(uint32_t lifeTime, uint64_t finalizedHeaderBlockNumber);
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Era& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Era& v);
