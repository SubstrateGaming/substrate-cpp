#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>
#include <optional>

#include <boost/multiprecision/cpp_int.hpp>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class LIB_SUBSTRATE_EXPORT IClient;
   using Client = std::shared_ptr<IClient>;

   using CompactInteger = boost::multiprecision::cpp_int;

   template <typename T, typename Tag, size_t TypeSize = sizeof(T)>
   class strong_type
   {
      T _value;
   public:
      explicit constexpr strong_type(T v) : _value(v) {}
      constexpr strong_type() : _value(T()) {}
      explicit operator T() const { return _value; }
      T value() const { return _value; }

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
      constexpr const uint8_t ExtrinsicVersion = 4;
   }
}
