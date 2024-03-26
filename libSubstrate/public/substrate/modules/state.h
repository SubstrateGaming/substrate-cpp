#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IState
   {
   public:
      virtual ~IState() = default;

      virtual std::optional<substrate::models::RuntimeVersion> getRuntimeVersion() const = 0;

   };
   using State = std::shared_ptr<IState>;
}
