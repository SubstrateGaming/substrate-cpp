#pragma once
#include "types.h"

#include "rpc/author.h"
#include "rpc/babe.h"
#include "rpc/beefy.h"
#include "rpc/chain.h"
#include "rpc/childstate.h"
#include "rpc/contracts.h"
#include "rpc/dev.h"
#include "rpc/engine.h"
#include "rpc/eth.h"
#include "rpc/eth_net.h"
#include "rpc/eth_web3.h"
#include "rpc/grandpa.h"
#include "rpc/mmr.h"
#include "rpc/offchain.h"
#include "rpc/payment.h"
#include "rpc/rpc.h"
#include "rpc/state.h"
#include "rpc/syncstate.h"
#include "rpc/system.h"

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
