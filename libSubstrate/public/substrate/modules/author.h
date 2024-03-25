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
      [[nodiscard]] virtual void submitExtrinsic(const std::string& extrinsic_encoded) const = 0;
   };
   using Author = std::shared_ptr<IAuthor>;
}
