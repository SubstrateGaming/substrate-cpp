#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT payment
   {
   public:
      virtual ~payment() = default;

      /**
       * @brief Query the detailed fee of a given encoded extrinsic
       * @deprecated This method is deprecated.
       * @param extrinsic Bytes
       * @param at BlockHash
       * @return FeeDetails
       */
      virtual FeeDetails payment_queryFeeDetails(Bytes extrinsic, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the fee information for an encoded extrinsic
       * @deprecated This method is deprecated.
       * @param extrinsic Bytes
       * @param at BlockHash
       * @return RuntimeDispatchInfoV1
       */
      virtual RuntimeDispatchInfoV1 payment_queryInfo(Bytes extrinsic, std::optional<BlockHash> at = std::nullopt) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_PAYMENT
#define SUBSTRATE_IMPL_RPC_PAYMENT \
   virtual FeeDetails payment_queryFeeDetails(Bytes extrinsic, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual RuntimeDispatchInfoV1 payment_queryInfo(Bytes extrinsic, std::optional<BlockHash> at = std::nullopt) const override;
#endif
