#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

bool substrate_client::author_hasKey(Bytes publicKey, Text keyType)
{
   return rpc<bool>("author_hasKey", publicKey, keyType);
}

bool substrate_client::author_hasSessionKeys(Bytes sessionKeys)
{
   return rpc<bool>("author_hasSessionKeys", sessionKeys);
}

Bytes substrate_client::author_insertKey(Text keyType, Text suri, Bytes publicKey)
{
   return rpc<Bytes>("author_insertKey", keyType, suri, publicKey);
}

Vec<Extrinsic> substrate_client::author_pendingExtrinsics()
{
   return rpc<Vec<Extrinsic>>("author_pendingExtrinsics");
}

Vec<Hash> substrate_client::author_removeExtrinsic(Vec<ExtrinsicOrHash> bytesOrHash)
{
   return rpc<Vec<Hash>>("author_removeExtrinsic", bytesOrHash);
}

Bytes substrate_client::author_rotateKeys()
{
   return rpc<Bytes>("author_rotateKeys");
}

ExtrinsicStatus substrate_client::author_submitAndWatchExtrinsic(Extrinsic extrinsic)
{
   return rpc<ExtrinsicStatus>("author_submitAndWatchExtrinsic", extrinsic);
}

Hash substrate_client::author_submitExtrinsic(Extrinsic extrinsic)
{
   return rpc<Hash>("author_submitExtrinsic", extrinsic);
}

