#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Bytes substrate_client::state_call(Text method, Bytes data, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageKey> substrate_client::state_getChildKeys(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

ReadProof substrate_client::state_getChildReadProof(PrefixedStorageKey childStorageKey, Vec<StorageKey> keys, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

StorageData substrate_client::state_getChildStorage(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Hash substrate_client::state_getChildStorageHash(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

u64 substrate_client::state_getChildStorageSize(StorageKey childStorageKey, StorageKey childDefinition, u32 childType, StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageKey> substrate_client::state_getKeys(StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageKey> substrate_client::state_getKeysPaged(StorageKey key, u32 count, std::optional<StorageKey> startKey, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Metadata substrate_client::state_getMetadata(std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<KeyValue> substrate_client::state_getPairs(StorageKey prefix, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

ReadProof substrate_client::state_getReadProof(Vec<StorageKey> keys, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

RuntimeVersion substrate_client::state_getRuntimeVersion(std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

StorageData substrate_client::state_getStorage(StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Hash substrate_client::state_getStorageHash(StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

u64 substrate_client::state_getStorageSize(StorageKey key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageChangeSet> substrate_client::state_queryStorage(Vec<StorageKey> keys, Hash fromBlock, std::optional<BlockHash> toBlock)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageChangeSet> substrate_client::state_queryStorageAt(Vec<StorageKey> keys, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

RuntimeVersion substrate_client::state_subscribeRuntimeVersion()
{
   throw std::runtime_error("not implemented");
}

StorageChangeSet substrate_client::state_subscribeStorage(std::optional<Vec<StorageKey>> keys)
{
   throw std::runtime_error("not implemented");
}

TraceBlockResponse substrate_client::state_traceBlock(Hash block, Option<Text> targets, Option<Text> storageKeys, Option<Text> methods)
{
   throw std::runtime_error("not implemented");
}

MigrationStatusResult substrate_client::state_trieMigrationStatus(std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

