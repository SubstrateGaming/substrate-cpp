#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Text substrate_client::web3_clientVersion()
{
   throw std::runtime_error("not implemented");
}

H256 substrate_client::web3_sha3(Bytes data)
{
   throw std::runtime_error("not implemented");
}

