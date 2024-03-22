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
