#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Option<EncodedFinalityProofs> substrate_client::grandpa_proveFinality(BlockNumber blockNumber)
{
   return rpc<Option<EncodedFinalityProofs>>("grandpa_proveFinality", blockNumber);
}

ReportedRoundStates substrate_client::grandpa_roundState()
{
   return rpc<ReportedRoundStates>("grandpa_roundState");
}

JustificationNotification substrate_client::grandpa_subscribeJustifications()
{
   return rpc<JustificationNotification>("grandpa_subscribeJustifications");
}

