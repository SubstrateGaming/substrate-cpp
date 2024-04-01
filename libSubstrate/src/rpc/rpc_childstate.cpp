#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Vec<StorageKey> substrate_client::childstate_getKeys(PrefixedStorageKey childKey, StorageKey prefix, std::optional<Hash> at)
{
   return rpc<Vec<StorageKey>>("childstate_getKeys", childKey, prefix, at);
}

Vec<StorageKey> substrate_client::childstate_getKeysPaged(PrefixedStorageKey childKey, StorageKey prefix, u32 count, std::optional<StorageKey> startKey, std::optional<Hash> at)
{
   return rpc<Vec<StorageKey>>("childstate_getKeysPaged", childKey, prefix, count, startKey, at);
}

Option<StorageData> substrate_client::childstate_getStorage(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   return rpc<Option<StorageData>>("childstate_getStorage", childKey, key, at);
}

Vec<Option<StorageData>> substrate_client::childstate_getStorageEntries(PrefixedStorageKey childKey, Vec<StorageKey> keys, std::optional<Hash> at)
{
   return rpc<Vec<Option<StorageData>>>("childstate_getStorageEntries", childKey, keys, at);
}

Option<Hash> substrate_client::childstate_getStorageHash(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   return rpc<Option<Hash>>("childstate_getStorageHash", childKey, key, at);
}

Option<u64> substrate_client::childstate_getStorageSize(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   return rpc<Option<u64>>("childstate_getStorageSize", childKey, key, at);
}

