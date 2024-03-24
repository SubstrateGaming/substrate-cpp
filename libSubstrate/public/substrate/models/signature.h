#pragma once
#include "../types.h"

namespace substrate::models
{
   struct Signature
   {
      uint8_t Type{0};
      std::vector<uint8_t> Bytes;
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Signature& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Signature& v);
