#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT chain
   {
   public:
      virtual ~chain() = default;

      /**
       * @brief Get header and body of a relay chain block
       * @param hash BlockHash
       * @return SignedBlock
       */
      virtual SignedBlock chain_getBlock(BlockHash hash = {}) = 0;

      /**
       * @brief Get the block hash for a specific block
       * @param blockNumber BlockNumber
       * @return BlockHash
       */
      virtual BlockHash chain_getBlockHash(BlockNumber blockNumber = {}) = 0;

      /**
       * @brief Get hash of the last finalized block in the canon chain
       * @return BlockHash
       */
      virtual BlockHash chain_getFinalizedHead() = 0;

      /**
       * @brief Retrieves the header for a specific block
       * @param hash BlockHash
       * @return Header
       */
      virtual Header chain_getHeader(BlockHash hash = {}) = 0;

      /**
       * @brief Retrieves the newest header via subscription
       * @return Header
       */
      virtual Header chain_subscribeAllHeads() = 0;

      /**
       * @brief Retrieves the best finalized header via subscription
       * @return Header
       */
      virtual Header chain_subscribeFinalizedHeads() = 0;

      /**
       * @brief Retrieves the best header via subscription
       * @return Header
       */
      virtual Header chain_subscribeNewHeads() = 0;
   };
}
