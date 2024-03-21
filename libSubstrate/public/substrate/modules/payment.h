#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IPayment
   {
   public:
      virtual ~IPayment() = default;
   };
   using Payment = std::shared_ptr<IPayment>;
}
