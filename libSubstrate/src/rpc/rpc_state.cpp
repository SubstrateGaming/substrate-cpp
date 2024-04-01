#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Bytes substrate_client::state_call(Text method, Bytes data, std::optional<BlockHash> at) const
{
   return rpc<Bytes>("state_call", method, data, at);
}

Vec<StorageKey> substrate_client::state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<Vec<StorageKey>>("state_getChildKeys", childStorageKey, childDefinition, childType, key, at);
}

ReadProof substrate_client::state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at) const
{
   return rpc<ReadProof>("state_getChildReadProof", childStorageKey, keys, at);
}

StorageData substrate_client::state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<StorageData>("state_getChildStorage", childStorageKey, childDefinition, childType, key, at);
}

Hash substrate_client::state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<Hash>("state_getChildStorageHash", childStorageKey, childDefinition, childType, key, at);
}

u64 substrate_client::state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<u64>("state_getChildStorageSize", childStorageKey, childDefinition, childType, key, at);
}

Vec<StorageKey> substrate_client::state_getKeys(StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<Vec<StorageKey>>("state_getKeys", key, at);
}

Vec<StorageKey> substrate_client::state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey, std::optional<BlockHash> at) const
{
   return rpc<Vec<StorageKey>>("state_getKeysPaged", key, count, startKey, at);
}

Metadata substrate_client::state_getMetadata(std::optional<BlockHash> at) const
{
   return rpc<Metadata>("state_getMetadata", at);
}

ReadProof substrate_client::state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at) const
{
   return rpc<ReadProof>("state_getReadProof", keys, at);
}

RuntimeVersion substrate_client::state_getRuntimeVersion(std::optional<BlockHash> at) const
{
   return rpc<RuntimeVersion>("state_getRuntimeVersion", at);
}

StorageData substrate_client::state_getStorage(StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<StorageData>("state_getStorage", key, at);
}

Hash substrate_client::state_getStorageHash(StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<Hash>("state_getStorageHash", key, at);
}

u64 substrate_client::state_getStorageSize(StorageKey key, std::optional<BlockHash> at) const
{
   return rpc<u64>("state_getStorageSize", key, at);
}

Vec<StorageChangeSet> substrate_client::state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at) const
{
   return rpc<Vec<StorageChangeSet>>("state_queryStorageAt", keys, at);
}

RuntimeVersion substrate_client::state_subscribeRuntimeVersion() const
{
   return rpc<RuntimeVersion>("state_subscribeRuntimeVersion");
}

StorageChangeSet substrate_client::state_subscribeStorage(std::optional<Vec<StorageKey>> keys) const
{
   return rpc<StorageChangeSet>("state_subscribeStorage", keys);
}

