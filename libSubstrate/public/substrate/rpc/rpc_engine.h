#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT engine
   {
   public:
      virtual ~engine() = default;

      /**
       * @brief Instructs the manual-seal authorship task to create a new block
       * @param createEmpty bool
       * @param finalize bool
       * @param parentHash BlockHash
       * @return CreatedBlock
       */
      virtual CreatedBlock engine_createBlock(bool createEmpty, bool finalize, std::optional<BlockHash> parentHash = std::nullopt) = 0;

      /**
       * @brief Instructs the manual-seal authorship task to finalize a block
       * @param hash BlockHash
       * @param justification Justification
       * @return bool
       */
      virtual bool engine_finalizeBlock(BlockHash hash, std::optional<Justification> justification = std::nullopt) = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_ENGINE
#define SUBSTRATE_IMPL_RPC_ENGINE \
   virtual CreatedBlock engine_createBlock(bool createEmpty, bool finalize, std::optional<BlockHash> parentHash = std::nullopt) override; \
   virtual bool engine_finalizeBlock(BlockHash hash, std::optional<Justification> justification = std::nullopt) override;
#endif
