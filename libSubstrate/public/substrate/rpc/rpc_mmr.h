#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT mmr
   {
   public:
      virtual ~mmr() = default;

      /**
       * @brief Generate MMR proof for the given block numbers.
       * @param blockNumbers Vec<u64>
       * @param bestKnownBlockNumber u64
       * @param at BlockHash
       * @return MmrLeafBatchProof
       */
      virtual MmrLeafBatchProof mmr_generateProof(Vec<u64> blockNumbers, std::optional<u64> bestKnownBlockNumber = std::nullopt, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Get the MMR root hash for the current best block.
       * @param at BlockHash
       * @return MmrHash
       */
      virtual MmrHash mmr_root(std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Verify an MMR proof
       * @param proof MmrLeafBatchProof
       * @return bool
       */
      virtual bool mmr_verifyProof(MmrLeafBatchProof proof) const = 0;

      /**
       * @brief Verify an MMR proof statelessly given an mmr_root
       * @param root MmrHash
       * @param proof MmrLeafBatchProof
       * @return bool
       */
      virtual bool mmr_verifyProofStateless(MmrHash root, MmrLeafBatchProof proof) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_MMR
#define SUBSTRATE_IMPL_RPC_MMR \
   virtual MmrLeafBatchProof mmr_generateProof(Vec<u64> blockNumbers, std::optional<u64> bestKnownBlockNumber = std::nullopt, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual MmrHash mmr_root(std::optional<BlockHash> at = std::nullopt) const override; \
   virtual bool mmr_verifyProof(MmrLeafBatchProof proof) const override; \
   virtual bool mmr_verifyProofStateless(MmrHash root, MmrLeafBatchProof proof) const override;
#endif
