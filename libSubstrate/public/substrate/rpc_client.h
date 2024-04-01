#pragma once
#include "types.h"

#include "rpc/rpc_author.h"
#include "rpc/rpc_chain.h"
#include "rpc/rpc_payment.h"
#include "rpc/rpc_state.h"
#include "rpc/rpc_system.h"

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT rpc_client :
      public author,
      public chain,
      public payment,
      public state,
      public system
   {
   public:
      virtual ~rpc_client() = default;
   };
}
#ifndef SUBSTRATE_IMPL_RPC_CLIENT
#define SUBSTRATE_IMPL_RPC_CLIENT \
   SUBSTRATE_IMPL_RPC_AUTHOR \
   SUBSTRATE_IMPL_RPC_CHAIN \
   SUBSTRATE_IMPL_RPC_PAYMENT \
   SUBSTRATE_IMPL_RPC_STATE \
   SUBSTRATE_IMPL_RPC_SYSTEM
#endif
