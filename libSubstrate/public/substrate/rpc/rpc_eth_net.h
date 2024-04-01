#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT eth_net
   {
   public:
      virtual ~eth_net() = default;

      /**
       * @brief Returns true if client is actively listening for network connections. Otherwise false.
       * @return bool
       */
      virtual bool net_listening() const = 0;

      /**
       * @brief Returns number of peers connected to node.
       * @return Text
       */
      virtual Text net_peerCount() const = 0;

      /**
       * @brief Returns protocol version.
       * @return Text
       */
      virtual Text net_version() const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_ETH_NET
#define SUBSTRATE_IMPL_RPC_ETH_NET \
   virtual bool net_listening() const override; \
   virtual Text net_peerCount() const override; \
   virtual Text net_version() const override;
#endif
