#pragma once

namespace substrate::models
{
   struct ChargeTypeBase
   {
   };

   struct ChargeAssetTxPayment : ChargeTypeBase
   {
      substrate::CompactInteger Tip;
      substrate::CompactInteger AssetId;
   };

   struct ChargeTransactionPayment : ChargeTypeBase
   {
      substrate::CompactInteger Tip;
   };

   // TODO: Make the ChargeType templated for Extrinsic type.
   using ChargeType = ChargeAssetTxPayment;
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeAssetTxPayment& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::ChargeAssetTxPayment& v);

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeTransactionPayment& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::ChargeTransactionPayment& v);
