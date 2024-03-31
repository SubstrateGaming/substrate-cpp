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
      virtual bool net_listening() = 0;

      /**
       * @brief Returns number of peers connected to node.
       * @return Text
       */
      virtual Text net_peerCount() = 0;

      /**
       * @brief Returns protocol version.
       * @return Text
       */
      virtual Text net_version() = 0;
   };
}
