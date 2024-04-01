#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Option<Bytes> substrate_client::offchain_localStorageGet(StorageKind kind, Bytes key) const
{
   return rpc<Option<Bytes>>("offchain_localStorageGet", kind, key);
}

Null substrate_client::offchain_localStorageSet(StorageKind kind, Bytes key, Bytes value) const
{
   return rpc<Null>("offchain_localStorageSet", kind, key, value);
}

