#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

bool substrate_client::author_hasKey(Bytes publicKey, Text keyType)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::author_hasSessionKeys(Bytes sessionKeys)
{
   throw std::runtime_error("not implemented");
}

Bytes substrate_client::author_insertKey(Text keyType, Text suri, Bytes publicKey)
{
   throw std::runtime_error("not implemented");
}

Vec<Extrinsic> substrate_client::author_pendingExtrinsics()
{
   throw std::runtime_error("not implemented");
}

Vec<Hash> substrate_client::author_removeExtrinsic(Vec<ExtrinsicOrHash> bytesOrHash)
{
   throw std::runtime_error("not implemented");
}

Bytes substrate_client::author_rotateKeys()
{
   throw std::runtime_error("not implemented");
}

ExtrinsicStatus substrate_client::author_submitAndWatchExtrinsic(Extrinsic extrinsic)
{
   throw std::runtime_error("not implemented");
}

Hash substrate_client::author_submitExtrinsic(Extrinsic extrinsic)
{
   throw std::runtime_error("not implemented");
}

