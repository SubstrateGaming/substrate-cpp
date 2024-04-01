#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Option<Bytes> substrate_client::offchain_localStorageGet(StorageKind kind, Bytes key)
{
   throw std::runtime_error("not implemented");
}

Null substrate_client::offchain_localStorageSet(StorageKind kind, Bytes key, Bytes value)
{
   throw std::runtime_error("not implemented");
}

