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
      virtual SignedBlock chain_getBlock(std::optional<BlockHash> hash = std::nullopt) const = 0;

      /**
       * @brief Get the block hash for a specific block
       * @param blockNumber BlockNumber
       * @return BlockHash
       */
      virtual BlockHash chain_getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const = 0;

      /**
       * @brief Get hash of the last finalized block in the canon chain
       * @return BlockHash
       */
      virtual BlockHash chain_getFinalizedHead() const = 0;

      /**
       * @brief Retrieves the header for a specific block
       * @param hash BlockHash
       * @return Header
       */
      virtual Header chain_getHeader(std::optional<BlockHash> hash = std::nullopt) const = 0;

      /**
       * @brief Retrieves the newest header via subscription
       * @return Header
       */
      virtual Header chain_subscribeAllHeads() const = 0;

      /**
       * @brief Retrieves the best finalized header via subscription
       * @return Header
       */
      virtual Header chain_subscribeFinalizedHeads() const = 0;

      /**
       * @brief Retrieves the best header via subscription
       * @return Header
       */
      virtual Header chain_subscribeNewHeads() const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_CHAIN
#define SUBSTRATE_IMPL_RPC_CHAIN \
   virtual SignedBlock chain_getBlock(std::optional<BlockHash> hash = std::nullopt) const override; \
   virtual BlockHash chain_getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const override; \
   virtual BlockHash chain_getFinalizedHead() const override; \
   virtual Header chain_getHeader(std::optional<BlockHash> hash = std::nullopt) const override; \
   virtual Header chain_subscribeAllHeads() const override; \
   virtual Header chain_subscribeFinalizedHeads() const override; \
   virtual Header chain_subscribeNewHeads() const override;
#endif
