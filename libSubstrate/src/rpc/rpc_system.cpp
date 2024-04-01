#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Index substrate_client::system_accountNextIndex(AccountId accountId)
{
   throw std::runtime_error("not implemented");
}

Null substrate_client::system_addLogFilter(Text directives)
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_addReservedPeer(Text peer)
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_chain()
{
   throw std::runtime_error("not implemented");
}

ChainType substrate_client::system_chainType()
{
   throw std::runtime_error("not implemented");
}

ApplyExtrinsicResult substrate_client::system_dryRun(Bytes extrinsic, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Health substrate_client::system_health()
{
   throw std::runtime_error("not implemented");
}

Vec<Text> substrate_client::system_localListenAddresses()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_localPeerId()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_name()
{
   throw std::runtime_error("not implemented");
}

NetworkState substrate_client::system_networkState()
{
   throw std::runtime_error("not implemented");
}

Vec<NodeRole> substrate_client::system_nodeRoles()
{
   throw std::runtime_error("not implemented");
}

Vec<PeerInfo> substrate_client::system_peers()
{
   throw std::runtime_error("not implemented");
}

ChainProperties substrate_client::system_properties()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_removeReservedPeer(Text peerId)
{
   throw std::runtime_error("not implemented");
}

Vec<Text> substrate_client::system_reservedPeers()
{
   throw std::runtime_error("not implemented");
}

Null substrate_client::system_resetLogFilter()
{
   throw std::runtime_error("not implemented");
}

SyncState substrate_client::system_syncState()
{
   throw std::runtime_error("not implemented");
}

Text substrate_client::system_version()
{
   throw std::runtime_error("not implemented");
}

