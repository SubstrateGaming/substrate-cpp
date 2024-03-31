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
      virtual MmrLeafBatchProof mmr_generateProof(Vec<u64> blockNumbers, u64 bestKnownBlockNumber = {}, BlockHash at = {}) = 0;

      /**
       * @brief Get the MMR root hash for the current best block.
       * @param at BlockHash
       * @return MmrHash
       */
      virtual MmrHash mmr_root(BlockHash at = {}) = 0;

      /**
       * @brief Verify an MMR proof
       * @param proof MmrLeafBatchProof
       * @return bool
       */
      virtual bool mmr_verifyProof(MmrLeafBatchProof proof) = 0;

      /**
       * @brief Verify an MMR proof statelessly given an mmr_root
       * @param root MmrHash
       * @param proof MmrLeafBatchProof
       * @return bool
       */
      virtual bool mmr_verifyProofStateless(MmrHash root, MmrLeafBatchProof proof) = 0;
   };
}
