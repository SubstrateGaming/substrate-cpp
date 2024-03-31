#pragma once
#include "../types.h"

namespace substrate::models
{
   struct HashTag { };
   struct Hash : strong_type<std::string, HashTag, 32>
   {
      using strong_type::strong_type;
   };
}

namespace substrate::rpc
{
   // TODO: Refactor
   using Hash = substrate::models::Hash;
   using BlockHash = Hash;
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Hash& v);
