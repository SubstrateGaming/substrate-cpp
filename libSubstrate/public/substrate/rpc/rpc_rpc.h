#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT rpc
   {
   public:
      virtual ~rpc() = default;

      /**
       * @brief Retrieves the list of RPC methods that are exposed by the node
       * @return RpcMethods
       */
      virtual RpcMethods rpc_methods() const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_RPC
#define SUBSTRATE_IMPL_RPC_RPC \
   virtual RpcMethods rpc_methods() const override;
#endif
