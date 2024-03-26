#pragma once
#include "../types.h"

namespace substrate::models
{
   struct RuntimeVersion
   {
      uint32_t AuthoringVersion{0};
      uint32_t ImplVersion{0};
      uint32_t SpecVersion{0};
      uint32_t TransactionVersion{0};
      std::string ImplName;
      std::string SpecName;
   };
}
