#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Text substrate_client::web3_clientVersion() const
{
   return rpc<Text>("web3_clientVersion");
}

H256 substrate_client::web3_sha3(Bytes data) const
{
   return rpc<H256>("web3_sha3", data);
}

