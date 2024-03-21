#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IAuthor
   {
   public:
      virtual ~IAuthor() = default;
   };
   using Author = std::shared_ptr<IAuthor>;
}
