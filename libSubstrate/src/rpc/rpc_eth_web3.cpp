#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Text substrate_client::web3_clientVersion()
{
   return rpc<Text>("web3_clientVersion");
}

H256 substrate_client::web3_sha3(Bytes data)
{
   return rpc<H256>("web3_sha3", data);
}

