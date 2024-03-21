#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IChain
   {
   public:
      virtual ~IChain() = default;
   };
   using Chain = std::shared_ptr<IChain>;
}
