#pragma once
#include "types.h"

#include "rpc/rpc_author.h"
#include "rpc/rpc_babe.h"
#include "rpc/rpc_beefy.h"
#include "rpc/rpc_chain.h"
#include "rpc/rpc_childstate.h"
#include "rpc/rpc_contracts.h"
#include "rpc/rpc_dev.h"
#include "rpc/rpc_engine.h"
#include "rpc/rpc_eth.h"
#include "rpc/rpc_eth_net.h"
#include "rpc/rpc_eth_web3.h"
#include "rpc/rpc_grandpa.h"
#include "rpc/rpc_mmr.h"
#include "rpc/rpc_offchain.h"
#include "rpc/rpc_payment.h"
#include "rpc/rpc_rpc.h"
#include "rpc/rpc_state.h"
#include "rpc/rpc_syncstate.h"
#include "rpc/rpc_system.h"

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT rpc_client :
      public author,
      public babe,
      public beefy,
      public chain,
      public childstate,
      public contracts,
      public dev,
      public engine,
      public eth,
      public eth_net,
      public eth_web3,
      public grandpa,
      public mmr,
      public offchain,
      public payment,
      public rpc,
      public state,
      public syncstate,
      public system
   {
   public:
      virtual ~rpc_client() = default;
   };
}
#ifndef SUBSTRATE_IMPL_RPC_CLIENT
#define SUBSTRATE_IMPL_RPC_CLIENT \
   SUBSTRATE_IMPL_RPC_AUTHOR \
   SUBSTRATE_IMPL_RPC_BABE \
   SUBSTRATE_IMPL_RPC_BEEFY \
   SUBSTRATE_IMPL_RPC_CHAIN \
   SUBSTRATE_IMPL_RPC_CHILDSTATE \
   SUBSTRATE_IMPL_RPC_CONTRACTS \
   SUBSTRATE_IMPL_RPC_DEV \
   SUBSTRATE_IMPL_RPC_ENGINE \
   SUBSTRATE_IMPL_RPC_ETH \
   SUBSTRATE_IMPL_RPC_ETH_NET \
   SUBSTRATE_IMPL_RPC_ETH_WEB3 \
   SUBSTRATE_IMPL_RPC_GRANDPA \
   SUBSTRATE_IMPL_RPC_MMR \
   SUBSTRATE_IMPL_RPC_OFFCHAIN \
   SUBSTRATE_IMPL_RPC_PAYMENT \
   SUBSTRATE_IMPL_RPC_RPC \
   SUBSTRATE_IMPL_RPC_STATE \
   SUBSTRATE_IMPL_RPC_SYNCSTATE \
   SUBSTRATE_IMPL_RPC_SYSTEM
#endif
