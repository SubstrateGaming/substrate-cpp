#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Option<Bytes> substrate_client::offchain_localStorageGet(StorageKind kind, Bytes key)
{
   return rpc<Option<Bytes>>("offchain_localStorageGet", kind, key);
}

Null substrate_client::offchain_localStorageSet(StorageKind kind, Bytes key, Bytes value)
{
   return rpc<Null>("offchain_localStorageSet", kind, key, value);
}

