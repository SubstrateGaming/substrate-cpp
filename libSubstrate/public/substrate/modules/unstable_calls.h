#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IUnstableCalls
   {
   public:
      virtual ~IUnstableCalls() = default;
   };
   using UnstableCalls = std::shared_ptr<IUnstableCalls>;
}
