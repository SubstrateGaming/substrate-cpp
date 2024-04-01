#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Index substrate_client::system_accountNextIndex(AccountId accountId)
{
   return rpc<Index>("system_accountNextIndex", accountId);
}

Null substrate_client::system_addLogFilter(Text directives)
{
   return rpc<Null>("system_addLogFilter", directives);
}

Text substrate_client::system_addReservedPeer(Text peer)
{
   return rpc<Text>("system_addReservedPeer", peer);
}

Text substrate_client::system_chain()
{
   return rpc<Text>("system_chain");
}

ChainType substrate_client::system_chainType()
{
   return rpc<ChainType>("system_chainType");
}

ApplyExtrinsicResult substrate_client::system_dryRun(Bytes extrinsic, std::optional<BlockHash> at)
{
   return rpc<ApplyExtrinsicResult>("system_dryRun", extrinsic, at);
}

Health substrate_client::system_health()
{
   return rpc<Health>("system_health");
}

Vec<Text> substrate_client::system_localListenAddresses()
{
   return rpc<Vec<Text>>("system_localListenAddresses");
}

Text substrate_client::system_localPeerId()
{
   return rpc<Text>("system_localPeerId");
}

Text substrate_client::system_name()
{
   return rpc<Text>("system_name");
}

NetworkState substrate_client::system_networkState()
{
   return rpc<NetworkState>("system_networkState");
}

Vec<NodeRole> substrate_client::system_nodeRoles()
{
   return rpc<Vec<NodeRole>>("system_nodeRoles");
}

Vec<PeerInfo> substrate_client::system_peers()
{
   return rpc<Vec<PeerInfo>>("system_peers");
}

ChainProperties substrate_client::system_properties()
{
   return rpc<ChainProperties>("system_properties");
}

Text substrate_client::system_removeReservedPeer(Text peerId)
{
   return rpc<Text>("system_removeReservedPeer", peerId);
}

Vec<Text> substrate_client::system_reservedPeers()
{
   return rpc<Vec<Text>>("system_reservedPeers");
}

Null substrate_client::system_resetLogFilter()
{
   return rpc<Null>("system_resetLogFilter");
}

SyncState substrate_client::system_syncState()
{
   return rpc<SyncState>("system_syncState");
}

Text substrate_client::system_version()
{
   return rpc<Text>("system_version");
}

