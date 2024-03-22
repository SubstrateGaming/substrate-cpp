#pragma once
#include "../types.h"
#include "era.h"
#include "charge_type.h"
#include "method.h"

namespace substrate::models
{
   struct Extrinsic
   {
      bool Signed{false};
      uint8_t TransactionVersion{0};
      Account Account;
      Era Era;
      CompactInteger Nonce;
      ChargeType Charge;
      Method Method;
      std::vector<uint8_t> Signature;
   };
}

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Extrinsic& v);
