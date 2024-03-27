#pragma once
#include "../types.h"

namespace substrate::modules
{
   using namespace substrate::models;

   class LIB_SUBSTRATE_EXPORT IAuthor
   {
   public:
      virtual ~IAuthor() = default;

      [[nodiscard]] virtual std::vector<Extrinsic> getPendingExtrinsic() const = 0;
      [[nodiscard]] virtual Hash submitExtrinsic(const Extrinsic& extrinsic) const = 0;
   };
   using Author = std::shared_ptr<IAuthor>;
}
