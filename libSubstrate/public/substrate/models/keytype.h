#pragma once

namespace substrate::models
{
   // https://github.com/paritytech/substrate/blob/8bc45ed4be61b83dcfac77bfc8002858ff8042ec/primitives/runtime/src/lib.rs#L230L240
   enum class KeyType
   {
      Unknown  = -1,

      /// Ed22519 signature
      Ed25519  = 0,

      /// Sr25519 signature
      Sr25519  = 1,

      /// ECDSA/SECP256k1 signature
      Ecdsa    = 2
   };
}
