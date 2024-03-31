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
      virtual RpcMethods rpc_methods() = 0;
   };
}
