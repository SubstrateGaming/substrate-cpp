#pragma once
#include <substrate/substrate.h>

namespace substrate::models::detail
{
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

   Payload make_payload(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion);
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::detail::Payload::extra_t& v);
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::detail::Payload::additional_t& v);
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::detail::Payload& v);
