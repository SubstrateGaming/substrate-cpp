#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT childstate
   {
   public:
      virtual ~childstate() = default;

      /**
       * @brief Returns the keys with prefix from a child storage, leave empty to get all the keys
       * @param childKey PrefixedStorageKey
       * @param prefix StorageKey
       * @param at Hash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> childstate_getKeys(PrefixedStorageKey childKey, StorageKey prefix, Hash at = {}) = 0;

      /**
       * @brief Returns the keys with prefix from a child storage with pagination support
       * @param childKey PrefixedStorageKey
       * @param prefix StorageKey
       * @param count u32
       * @param startKey StorageKey
       * @param at Hash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> childstate_getKeysPaged(PrefixedStorageKey childKey, StorageKey prefix, u32 count, StorageKey startKey = {}, Hash at = {}) = 0;

      /**
       * @brief Returns a child storage entry at a specific block state
       * @param childKey PrefixedStorageKey
       * @param key StorageKey
       * @param at Hash
       * @return Option<StorageData>
       */
      virtual Option<StorageData> childstate_getStorage(PrefixedStorageKey childKey, StorageKey key, Hash at = {}) = 0;

      /**
       * @brief Returns child storage entries for multiple keys at a specific block state
       * @param childKey PrefixedStorageKey
       * @param keys Vec<StorageKey>
       * @param at Hash
       * @return Vec<Option<StorageData>>
       */
      virtual Vec<Option<StorageData>> childstate_getStorageEntries(PrefixedStorageKey childKey, Vec<StorageKey> keys, Hash at = {}) = 0;

      /**
       * @brief Returns the hash of a child storage entry at a block state
       * @param childKey PrefixedStorageKey
       * @param key StorageKey
       * @param at Hash
       * @return Option<Hash>
       */
      virtual Option<Hash> childstate_getStorageHash(PrefixedStorageKey childKey, StorageKey key, Hash at = {}) = 0;

      /**
       * @brief Returns the size of a child storage entry at a block state
       * @param childKey PrefixedStorageKey
       * @param key StorageKey
       * @param at Hash
       * @return Option<u64>
       */
      virtual Option<u64> childstate_getStorageSize(PrefixedStorageKey childKey, StorageKey key, Hash at = {}) = 0;
   };
}
