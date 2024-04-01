#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

FeeDetails substrate_client::payment_queryFeeDetails(Bytes extrinsic, std::optional<BlockHash> at) const
{
   return rpc<FeeDetails>("payment_queryFeeDetails", extrinsic, at);
}

RuntimeDispatchInfoV1 substrate_client::payment_queryInfo(Bytes extrinsic, std::optional<BlockHash> at) const
{
   return rpc<RuntimeDispatchInfoV1>("payment_queryInfo", extrinsic, at);
}

