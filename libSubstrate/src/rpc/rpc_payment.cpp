#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

FeeDetails substrate_client::payment_queryFeeDetails(Bytes extrinsic, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

RuntimeDispatchInfoV1 substrate_client::payment_queryInfo(Bytes extrinsic, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

