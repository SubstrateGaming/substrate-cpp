#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Vec<Extrinsic> substrate_client::author_pendingExtrinsics() const
{
   return rpc<Vec<Extrinsic>>("author_pendingExtrinsics");
}

std::string substrate_client::author_submitAndWatchExtrinsic(subscription_callback_t callback, Extrinsic extrinsic) const
{
   return rpc<std::string>("author_submitAndWatchExtrinsic", callback, extrinsic);
}

Hash substrate_client::author_submitExtrinsic(Extrinsic extrinsic) const
{
   return rpc<Hash>("author_submitExtrinsic", extrinsic);
}

