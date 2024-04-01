#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Index substrate_client::system_accountNextIndex(AccountId accountId) const
{
   return rpc<Index>("system_accountNextIndex", accountId);
}

Text substrate_client::system_chain() const
{
   return rpc<Text>("system_chain");
}

ChainType substrate_client::system_chainType() const
{
   return rpc<ChainType>("system_chainType");
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

Vec<NodeRole> substrate_client::system_nodeRoles() const
{
   return rpc<Vec<NodeRole>>("system_nodeRoles");
}

ChainProperties substrate_client::system_properties() const
{
   return rpc<ChainProperties>("system_properties");
}

Vec<Text> substrate_client::system_reservedPeers() const
{
   return rpc<Vec<Text>>("system_reservedPeers");
}

SyncState substrate_client::system_syncState() const
{
   return rpc<SyncState>("system_syncState");
}

Text substrate_client::system_version() const
{
   return rpc<Text>("system_version");
}

