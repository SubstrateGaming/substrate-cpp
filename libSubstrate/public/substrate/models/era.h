#pragma once
#include "../types.h"

namespace substrate::models
{
   struct Era
   {
      bool IsImmortal{false};
      uint64_t Period{0};
      uint64_t Phase{0};
   };
}
