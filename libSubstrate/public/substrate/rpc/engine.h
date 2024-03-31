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
      virtual CreatedBlock engine_createBlock(bool createEmpty, bool finalize, BlockHash parentHash = {}) = 0;

      /**
       * @brief Instructs the manual-seal authorship task to finalize a block
       * @param hash BlockHash
       * @param justification Justification
       * @return bool
       */
      virtual bool engine_finalizeBlock(BlockHash hash, Justification justification = {}) = 0;
   };
}
