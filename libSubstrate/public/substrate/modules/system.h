#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT ISystem
   {
   public:
      virtual ~ISystem() = default;
   };
   using System = std::shared_ptr<ISystem>;
}
