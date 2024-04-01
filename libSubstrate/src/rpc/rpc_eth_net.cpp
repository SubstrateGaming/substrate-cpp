#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

bool substrate_client::net_listening()
{
   return rpc<bool>("net_listening");
}

Text substrate_client::net_peerCount()
{
   return rpc<Text>("net_peerCount");
}

Text substrate_client::net_version()
{
   return rpc<Text>("net_version");
}

