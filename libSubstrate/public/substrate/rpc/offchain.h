#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT offchain
   {
   public:
      virtual ~offchain() = default;

      /**
       * @brief Get offchain local storage under given key and prefix
       * @warning This method is marked as unsafe.
       * @param kind StorageKind
       * @param key Bytes
       * @return Option<Bytes>
       */
      virtual Option<Bytes> offchain_localStorageGet(StorageKind kind, Bytes key) = 0;

      /**
       * @brief Set offchain local storage under given key and prefix
       * @warning This method is marked as unsafe.
       * @param kind StorageKind
       * @param key Bytes
       * @param value Bytes
       * @return Null
       */
      virtual Null offchain_localStorageSet(StorageKind kind, Bytes key, Bytes value) = 0;
   };
}
