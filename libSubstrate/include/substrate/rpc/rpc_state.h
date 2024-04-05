#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT state
   {
   public:
      virtual ~state() = default;

      /**
       * @brief Perform a call to a builtin on the chain
       * @param method Text
       * @param data Bytes
       * @param at BlockHash
       * @return Bytes
       */
      virtual Bytes state_call(Text method, Bytes data, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the keys with prefix of a specific child storage
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns proof of storage for child key entries at a specific block state.
       * @param childStorageKey PrefixedStorageKey
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return ReadProof
       */
      virtual ReadProof state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the child storage for a key
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return StorageData
       */
      virtual StorageData state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the child storage hash
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return Hash
       */
      virtual Hash state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the child storage size
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return u64
       */
      virtual u64 state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the keys with a certain prefix
       * @deprecated This method is deprecated.
       * @param key StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getKeys(StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns the keys with prefix with pagination support.
       * @param key StorageKey
       * @param count u32
       * @param startKey StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey = std::nullopt, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns the runtime metadata
       * @param at BlockHash
       * @return Metadata
       */
      virtual Metadata state_getMetadata(std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns proof of storage entries at a specific block state
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return ReadProof
       */
      virtual ReadProof state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Get the runtime version
       * @param at BlockHash
       * @return RuntimeVersion
       */
      virtual RuntimeVersion state_getRuntimeVersion(std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the storage for a key
       * @param key StorageKey
       * @param at BlockHash
       * @return StorageData
       */
      virtual StorageData state_getStorage(StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the storage hash
       * @param key StorageKey
       * @param at BlockHash
       * @return Hash
       */
      virtual Hash state_getStorageHash(StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the storage size
       * @param key StorageKey
       * @param at BlockHash
       * @return u64
       */
      virtual u64 state_getStorageSize(StorageKey key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Query storage entries (by key) starting at block hash given as the second parameter
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return Vec<StorageChangeSet>
       */
      virtual Vec<StorageChangeSet> state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Retrieves the runtime version via subscription
       * @param callback subscription_callback_t
       * @return std::string
       */
      virtual std::string state_subscribeRuntimeVersion(subscription_callback_t callback) const = 0;

      /**
       * @brief Subscribes to storage changes for the provided keys
       * @param callback subscription_callback_t
       * @param keys Vec<StorageKey>
       * @return std::string
       */
      virtual std::string state_subscribeStorage(subscription_callback_t callback, std::optional<Vec<StorageKey>> keys = std::nullopt) const = 0;

   };
}

#ifndef SUBSTRATE_IMPL_RPC_STATE
#define SUBSTRATE_IMPL_RPC_STATE \
   virtual Bytes state_call(Text method, Bytes data, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Vec<StorageKey> state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual ReadProof state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual StorageData state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Hash state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual u64 state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Vec<StorageKey> state_getKeys(StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Vec<StorageKey> state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey = std::nullopt, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Metadata state_getMetadata(std::optional<BlockHash> at = std::nullopt) const override; \
   virtual ReadProof state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual RuntimeVersion state_getRuntimeVersion(std::optional<BlockHash> at = std::nullopt) const override; \
   virtual StorageData state_getStorage(StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Hash state_getStorageHash(StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual u64 state_getStorageSize(StorageKey key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Vec<StorageChangeSet> state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual std::string state_subscribeRuntimeVersion(subscription_callback_t callback) const override; \
   virtual std::string state_subscribeStorage(subscription_callback_t callback, std::optional<Vec<StorageKey>> keys = std::nullopt) const override;
#endif
