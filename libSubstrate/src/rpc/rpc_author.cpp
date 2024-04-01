#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Vec<Extrinsic> substrate_client::author_pendingExtrinsics() const
{
   return rpc<Vec<Extrinsic>>("author_pendingExtrinsics");
}

ExtrinsicStatus substrate_client::author_submitAndWatchExtrinsic(Extrinsic extrinsic) const
{
   return rpc<ExtrinsicStatus>("author_submitAndWatchExtrinsic", extrinsic);
}

Hash substrate_client::author_submitExtrinsic(Extrinsic extrinsic) const
{
   return rpc<Hash>("author_submitExtrinsic", extrinsic);
}

