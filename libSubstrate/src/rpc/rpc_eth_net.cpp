#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

bool substrate_client::net_listening()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::net_peerCount()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::net_version()
{
   throw std::runtime_error("not implemented");
}

