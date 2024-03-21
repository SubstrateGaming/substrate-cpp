#pragma once
#include "../types.h"

namespace substrate::modules
{
   class LIB_SUBSTRATE_EXPORT IChain
   {
   public:
      virtual ~IChain() = default;

      [[nodiscard]] virtual std::optional<BlockData> getBlock(std::optional<Hash> hash = std::nullopt) const = 0;
      [[nodiscard]] virtual std::optional<Hash> getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const = 0;
      [[nodiscard]] virtual std::optional<Hash> getFinalizedHead() const = 0;
      [[nodiscard]] virtual std::optional<Header> getHeader(std::optional<Hash> hash = std::nullopt) const = 0;

      // Subscribe

   };
   using Chain = std::shared_ptr<IChain>;
}
