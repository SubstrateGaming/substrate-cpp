#pragma once
#include "../types.h"
#include "era.h"
#include "charge_type.h"
#include "method.h"
#include "signature.h"
#include "hash.h"
#include "rpc.h"

namespace substrate::models
{
   struct Extrinsic
   {
      bool Signed{false};
      uint8_t TransactionVersion{0};
      AccountId32 Account;
      Era Era;
      CompactInteger Nonce;
      ChargeType Charge;
      Method Method;
      Signature Signature;
   };
}

namespace substrate::rpc
{
   // TODO: Refactor
   using Extrinsic = substrate::models::Extrinsic;
}


LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Extrinsic& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Extrinsic& v);
