#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT eth_web3
   {
   public:
      virtual ~eth_web3() = default;

      /**
       * @brief Returns current client version.
       * @return Text
       */
      virtual Text web3_clientVersion() const = 0;

      /**
       * @brief Returns sha3 of the given data
       * @param data Bytes
       * @return H256
       */
      virtual H256 web3_sha3(Bytes data) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_ETH_WEB3
#define SUBSTRATE_IMPL_RPC_ETH_WEB3 \
   virtual Text web3_clientVersion() const override; \
   virtual H256 web3_sha3(Bytes data) const override;
#endif
