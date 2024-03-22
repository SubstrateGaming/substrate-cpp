#pragma once
#include "../types.h"
#include "keytype.h"

namespace substrate::models
{
   struct AccountIdTag { };
   struct AccountId : strong_type<std::string, AccountIdTag, 32>
   {
      using strong_type::strong_type;
   };

   struct Account : AccountId
   {
      KeyType KeyType{KeyType::Unknown};
      std::vector<uint8_t> PrivateKey;
   };
}
