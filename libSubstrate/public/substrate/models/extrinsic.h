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

   // TODO: Do we want to have this exposed?
   struct Payload
   {
      struct extra_t
      {
         Era Mortality;
         CompactInteger Nonce;
         ChargeType Charge;
      };

      struct additional_t
      {
         uint32_t SpecVersion;
         uint32_t TransactionVersion;
         Hash GenesisHash;
         // Immortal: Use Genesis Hash
         //           otherwise use StartEra
         Hash CheckpointHash;
      };

      Method Call;
      extra_t Extra;
      additional_t Additional;
   };

   LIB_SUBSTRATE_EXPORT Payload make_payload(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion);
}


LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload::extra_t& v);
LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload::additional_t& v);
LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload& v);
LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Extrinsic& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Extrinsic& v);
