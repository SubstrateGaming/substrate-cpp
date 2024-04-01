#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

HashMap<AuthorityId, EpochAuthorship> substrate_client::babe_epochAuthorship() const
{
   return rpc<HashMap<AuthorityId, EpochAuthorship>>("babe_epochAuthorship");
}

