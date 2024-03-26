#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT ISystem
   {
   public:
      virtual ~ISystem() = default;

      [[nodiscard]] virtual uint32_t getAccountNextIndex(const std::string& ss58_address) const = 0;
   };
   using System = std::shared_ptr<ISystem>;
}
