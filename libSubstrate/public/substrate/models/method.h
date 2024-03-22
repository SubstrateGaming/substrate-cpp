#pragma once
#include "../types.h"

namespace substrate::models
{
   struct Method
   {
      std::string ModuleName;
      uint8_t ModuleIndex{0};
      std::string CallName;
      uint8_t CallIndex{0};
      std::vector<uint8_t> Parameters;
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Method& v);
