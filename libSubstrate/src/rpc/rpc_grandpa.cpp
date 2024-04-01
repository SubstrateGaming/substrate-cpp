#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Option<EncodedFinalityProofs> substrate_client::grandpa_proveFinality(BlockNumber blockNumber)
{
   throw std::runtime_error("not implemented");
}

ReportedRoundStates substrate_client::grandpa_roundState()
{
   throw std::runtime_error("not implemented");
}

JustificationNotification substrate_client::grandpa_subscribeJustifications()
{
   throw std::runtime_error("not implemented");
}

