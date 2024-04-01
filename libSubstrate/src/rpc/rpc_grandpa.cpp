#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Option<EncodedFinalityProofs> substrate_client::grandpa_proveFinality(BlockNumber blockNumber) const
{
   return rpc<Option<EncodedFinalityProofs>>("grandpa_proveFinality", blockNumber);
}

ReportedRoundStates substrate_client::grandpa_roundState() const
{
   return rpc<ReportedRoundStates>("grandpa_roundState");
}

JustificationNotification substrate_client::grandpa_subscribeJustifications() const
{
   return rpc<JustificationNotification>("grandpa_subscribeJustifications");
}

