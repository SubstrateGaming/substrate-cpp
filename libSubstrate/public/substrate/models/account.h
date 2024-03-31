#pragma once
#include "../types.h"
#include "keytype.h"

namespace substrate::models
{
   struct AccountIdTag { };
   struct AccountId32 : strong_type<std::string, AccountIdTag, 32>
   {
      using strong_type::strong_type;
   };
}

namespace substrate::rpc
{
   // TODO: Refactor
   using AccountId = substrate::models::AccountId32;
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::AccountId32& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::AccountId32& v);
