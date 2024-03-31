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
      virtual Text web3_clientVersion() = 0;

      /**
       * @brief Returns sha3 of the given data
       * @param data Bytes
       * @return H256
       */
      virtual H256 web3_sha3(Bytes data) = 0;
   };
}
