#pragma once
#include "../types.h"

namespace substrate::models
{
   struct Signature
   {
      KeyType Type{0};
      substrate::bytes Bytes;
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Signature& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Signature& v);
