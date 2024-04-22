#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>

#include <math/wide_integer/uintwide_t.h>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   namespace rpc
   {
      class LIB_SUBSTRATE_EXPORT IClient;
      using Client = std::shared_ptr<IClient>;
   }

   class LIB_SUBSTRATE_EXPORT ICrypto;
   using Crypto = std::shared_ptr<ICrypto>;

   using bytes = std::vector<uint8_t>;

   // Must match libscale's CompactInteger.
   using CompactInteger = math::wide_integer::uint256_t;

   template <typename T, typename Tag, size_t TypeSize = sizeof(T)>
   class strong_type
   {
      T _value;
   public:
      explicit constexpr strong_type(T v) : _value(v) {}
      constexpr strong_type() : _value(T()) {}
      explicit operator T() const { return _value; }
      T& value() { return _value; }
      const T& const_value() const { return _value; }

      static size_t GetTypeSize() { return TypeSize; }
   };

   namespace constants
   {
      /// <summary>
      /// The address version
      ///  https://polkadot.js.org/docs/api/FAQ/
      ///  0 = AccountId (no prefix), 1 = IndicesLookup (0xFF), 2 = MutiAddress (https://github.com/paritytech/substrate/pull/7380)
      /// </summary>
      constexpr const uint32_t AddressVersion = 2;

      // https://github.com/paritytech/substrate/blob/c0cb70419798eb7fd38806da668bec05f8cfd7f1/primitives/runtime/src/generic/unchecked_extrinsic.rs#L33
      // aka TRANSACTION_VERSION
      constexpr const uint8_t TransactionVersion = 4;
   }
}
