#pragma once
#include "../types.h"

namespace substrate::modules
{
   using namespace substrate::models;

   class LIB_SUBSTRATE_EXPORT IChain
   {

   public:
      virtual ~IChain() = default;

      [[nodiscard]] virtual BlockData getBlock(std::optional<Hash> hash = std::nullopt) const = 0;
      [[nodiscard]] virtual Hash getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const = 0;
      [[nodiscard]] virtual Hash getFinalizedHead() const = 0;
      [[nodiscard]] virtual Header getHeader(std::optional<Hash> hash = std::nullopt) const = 0;

      // Subscribe

   };
   using Chain = std::shared_ptr<IChain>;
}
