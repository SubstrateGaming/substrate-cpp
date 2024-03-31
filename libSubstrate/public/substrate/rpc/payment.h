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
      virtual FeeDetails payment_queryFeeDetails(Bytes extrinsic, BlockHash at = {}) = 0;

      /**
       * @brief Retrieves the fee information for an encoded extrinsic
       * @deprecated This method is deprecated.
       * @param extrinsic Bytes
       * @param at BlockHash
       * @return RuntimeDispatchInfoV1
       */
      virtual RuntimeDispatchInfoV1 payment_queryInfo(Bytes extrinsic, BlockHash at = {}) = 0;
   };
}
