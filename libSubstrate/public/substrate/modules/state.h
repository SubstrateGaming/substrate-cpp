#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IState
   {
   public:
      virtual ~IState() = default;
   };
   using State = std::shared_ptr<IState>;
}
