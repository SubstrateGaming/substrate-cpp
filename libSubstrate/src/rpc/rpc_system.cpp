#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Index substrate_client::system_accountNextIndex(AccountId accountId) const
{
   return rpc<Index>("system_accountNextIndex", accountId);
}

Null substrate_client::system_addLogFilter(Text directives) const
{
   return rpc<Null>("system_addLogFilter", directives);
}

Text substrate_client::system_addReservedPeer(Text peer) const
{
   return rpc<Text>("system_addReservedPeer", peer);
}

Text substrate_client::system_chain() const
{
   return rpc<Text>("system_chain");
}

ChainType substrate_client::system_chainType() const
{
   return rpc<ChainType>("system_chainType");
}

ApplyExtrinsicResult substrate_client::system_dryRun(Bytes extrinsic, std::optional<BlockHash> at) const
{
   return rpc<ApplyExtrinsicResult>("system_dryRun", extrinsic, at);
}

Health substrate_client::system_health() const
{
   return rpc<Health>("system_health");
}

Vec<Text> substrate_client::system_localListenAddresses() const
{
   return rpc<Vec<Text>>("system_localListenAddresses");
}

Text substrate_client::system_localPeerId() const
{
   return rpc<Text>("system_localPeerId");
}

Text substrate_client::system_name() const
{
   return rpc<Text>("system_name");
}

NetworkState substrate_client::system_networkState() const
{
   return rpc<NetworkState>("system_networkState");
}

Vec<NodeRole> substrate_client::system_nodeRoles() const
{
   return rpc<Vec<NodeRole>>("system_nodeRoles");
}

Vec<PeerInfo> substrate_client::system_peers() const
{
   return rpc<Vec<PeerInfo>>("system_peers");
}

ChainProperties substrate_client::system_properties() const
{
   return rpc<ChainProperties>("system_properties");
}

Text substrate_client::system_removeReservedPeer(Text peerId) const
{
   return rpc<Text>("system_removeReservedPeer", peerId);
}

Vec<Text> substrate_client::system_reservedPeers() const
{
   return rpc<Vec<Text>>("system_reservedPeers");
}

Null substrate_client::system_resetLogFilter() const
{
   return rpc<Null>("system_resetLogFilter");
}

SyncState substrate_client::system_syncState() const
{
   return rpc<SyncState>("system_syncState");
}

Text substrate_client::system_version() const
{
   return rpc<Text>("system_version");
}

