#pragma once

namespace substrate::models
{
   struct ChargeType
   {
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeType& v);
