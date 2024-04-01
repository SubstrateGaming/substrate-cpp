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
      virtual Bytes state_call(Text method, Bytes data, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the keys with prefix of a specific child storage
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Returns proof of storage for child key entries at a specific block state.
       * @param childStorageKey PrefixedStorageKey
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return ReadProof
       */
      virtual ReadProof state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the child storage for a key
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return StorageData
       */
      virtual StorageData state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the child storage hash
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return Hash
       */
      virtual Hash state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the child storage size
       * @param childStorageKey StorageKey
       * @param childDefinition StorageKey
       * @param childType u32
       * @param key StorageKey
       * @param at BlockHash
       * @return u64
       */
      virtual u64 state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the keys with a certain prefix
       * @deprecated This method is deprecated.
       * @param key StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getKeys(StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Returns the keys with prefix with pagination support.
       * @param key StorageKey
       * @param count u32
       * @param startKey StorageKey
       * @param at BlockHash
       * @return Vec<StorageKey>
       */
      virtual Vec<StorageKey> state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey = std::nullopt, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Returns the runtime metadata
       * @param at BlockHash
       * @return Metadata
       */
      virtual Metadata state_getMetadata(std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Returns the keys with prefix, leave empty to get all the keys (deprecated: Use getKeysPaged)
       * @warning This method is marked as unsafe.
       * @deprecated This method is deprecated.
       * @param prefix StorageKey
       * @param at BlockHash
       * @return Vec<KeyValue>
       */
      virtual Vec<KeyValue> state_getPairs(StorageKey prefix, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Returns proof of storage entries at a specific block state
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return ReadProof
       */
      virtual ReadProof state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Get the runtime version
       * @param at BlockHash
       * @return RuntimeVersion
       */
      virtual RuntimeVersion state_getRuntimeVersion(std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the storage for a key
       * @param key StorageKey
       * @param at BlockHash
       * @return StorageData
       */
      virtual StorageData state_getStorage(StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the storage hash
       * @param key StorageKey
       * @param at BlockHash
       * @return Hash
       */
      virtual Hash state_getStorageHash(StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the storage size
       * @param key StorageKey
       * @param at BlockHash
       * @return u64
       */
      virtual u64 state_getStorageSize(StorageKey key, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Query historical storage entries (by key) starting from a start block
       * @warning This method is marked as unsafe.
       * @param keys Vec<StorageKey>
       * @param fromBlock Hash
       * @param toBlock BlockHash
       * @return Vec<StorageChangeSet>
       */
      virtual Vec<StorageChangeSet> state_queryStorage(Vec<StorageKey> keys, Hash fromBlock, std::optional<BlockHash> toBlock = std::nullopt) = 0;

      /**
       * @brief Query storage entries (by key) starting at block hash given as the second parameter
       * @param keys Vec<StorageKey>
       * @param at BlockHash
       * @return Vec<StorageChangeSet>
       */
      virtual Vec<StorageChangeSet> state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) = 0;

      /**
       * @brief Retrieves the runtime version via subscription
       * @return RuntimeVersion
       */
      virtual RuntimeVersion state_subscribeRuntimeVersion() = 0;

      /**
       * @brief Subscribes to storage changes for the provided keys
       * @param keys Vec<StorageKey>
       * @return StorageChangeSet
       */
      virtual StorageChangeSet state_subscribeStorage(std::optional<Vec<StorageKey>> keys = std::nullopt) = 0;

      /**
       * @brief Provides a way to trace the re-execution of a single block
       * @warning This method is marked as unsafe.
       * @param block Hash
       * @param targets Option<Text>
       * @param storageKeys Option<Text>
       * @param methods Option<Text>
       * @return TraceBlockResponse
       */
      virtual TraceBlockResponse state_traceBlock(Hash block, Option<Text> targets, Option<Text> storageKeys, Option<Text> methods) = 0;

      /**
       * @brief Check current migration state
       * @warning This method is marked as unsafe.
       * @param at BlockHash
       * @return MigrationStatusResult
       */
      virtual MigrationStatusResult state_trieMigrationStatus(std::optional<BlockHash> at = std::nullopt) = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_STATE
#define SUBSTRATE_IMPL_RPC_STATE \
   virtual Bytes state_call(Text method, Bytes data, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Vec<StorageKey> state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual ReadProof state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) override; \
   virtual StorageData state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Hash state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual u64 state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Vec<StorageKey> state_getKeys(StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Vec<StorageKey> state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey = std::nullopt, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Metadata state_getMetadata(std::optional<BlockHash> at = std::nullopt) override; \
   virtual Vec<KeyValue> state_getPairs(StorageKey prefix, std::optional<BlockHash> at = std::nullopt) override; \
   virtual ReadProof state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) override; \
   virtual RuntimeVersion state_getRuntimeVersion(std::optional<BlockHash> at = std::nullopt) override; \
   virtual StorageData state_getStorage(StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Hash state_getStorageHash(StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual u64 state_getStorageSize(StorageKey key, std::optional<BlockHash> at = std::nullopt) override; \
   virtual Vec<StorageChangeSet> state_queryStorage(Vec<StorageKey> keys, Hash fromBlock, std::optional<BlockHash> toBlock = std::nullopt) override; \
   virtual Vec<StorageChangeSet> state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at = std::nullopt) override; \
   virtual RuntimeVersion state_subscribeRuntimeVersion() override; \
   virtual StorageChangeSet state_subscribeStorage(std::optional<Vec<StorageKey>> keys = std::nullopt) override; \
   virtual TraceBlockResponse state_traceBlock(Hash block, Option<Text> targets, Option<Text> storageKeys, Option<Text> methods) override; \
   virtual MigrationStatusResult state_trieMigrationStatus(std::optional<BlockHash> at = std::nullopt) override;
#endif
