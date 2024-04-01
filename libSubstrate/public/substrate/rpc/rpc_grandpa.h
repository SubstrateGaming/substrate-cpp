#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT grandpa
   {
   public:
      virtual ~grandpa() = default;

      /**
       * @brief Prove finality for the given block number, returning the Justification for the last block in the set.
       * @param blockNumber BlockNumber
       * @return Option<EncodedFinalityProofs>
       */
      virtual Option<EncodedFinalityProofs> grandpa_proveFinality(BlockNumber blockNumber) = 0;

      /**
       * @brief Returns the state of the current best round state as well as the ongoing background rounds
       * @return ReportedRoundStates
       */
      virtual ReportedRoundStates grandpa_roundState() = 0;

      /**
       * @brief Subscribes to grandpa justifications
       * @return JustificationNotification
       */
      virtual JustificationNotification grandpa_subscribeJustifications() = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_GRANDPA
#define SUBSTRATE_IMPL_RPC_GRANDPA \
   virtual Option<EncodedFinalityProofs> grandpa_proveFinality(BlockNumber blockNumber) override; \
   virtual ReportedRoundStates grandpa_roundState() override; \
   virtual JustificationNotification grandpa_subscribeJustifications() override;
#endif
