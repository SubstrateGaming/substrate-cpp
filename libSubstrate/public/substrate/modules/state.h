#pragma once
#include "../types.h"

namespace substrate::modules
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

   class LIB_SUBSTRATE_EXPORT IState
   {
   public:
      virtual ~IState() = default;

      virtual std::optional<RuntimeVersion> getRuntimeVersion() const = 0;

   };
   using State = std::shared_ptr<IState>;
}
