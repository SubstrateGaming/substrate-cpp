#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT beefy
   {
   public:
      virtual ~beefy() = default;

      /**
       * @brief Returns hash of the latest BEEFY finalized block as seen by this client.
       * @return H256
       */
      virtual H256 beefy_getFinalizedHead() = 0;

      /**
       * @brief Returns the block most recently finalized by BEEFY, alongside its justification.
       * @return BeefyVersionedFinalityProof
       */
      virtual BeefyVersionedFinalityProof beefy_subscribeJustifications() = 0;
   };
}
