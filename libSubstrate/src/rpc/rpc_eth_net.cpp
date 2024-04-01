#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

bool substrate_client::net_listening() const
{
   return rpc<bool>("net_listening");
}

Text substrate_client::net_peerCount() const
{
   return rpc<Text>("net_peerCount");
}

Text substrate_client::net_version() const
{
   return rpc<Text>("net_version");
}

