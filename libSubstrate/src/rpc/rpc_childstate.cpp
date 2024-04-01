#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Vec<StorageKey> substrate_client::childstate_getKeys(PrefixedStorageKey childKey, StorageKey prefix, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<StorageKey> substrate_client::childstate_getKeysPaged(PrefixedStorageKey childKey, StorageKey prefix, u32 count, std::optional<StorageKey> startKey, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

Option<StorageData> substrate_client::childstate_getStorage(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

Vec<Option<StorageData>> substrate_client::childstate_getStorageEntries(PrefixedStorageKey childKey, Vec<StorageKey> keys, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

Option<Hash> substrate_client::childstate_getStorageHash(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

Option<u64> substrate_client::childstate_getStorageSize(PrefixedStorageKey childKey, StorageKey key, std::optional<Hash> at)
{
   throw std::runtime_error("not implemented");
}

