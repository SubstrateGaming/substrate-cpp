#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

HashMap<AuthorityId, EpochAuthorship> substrate_client::babe_epochAuthorship()
{
   throw std::runtime_error("not implemented");
}

