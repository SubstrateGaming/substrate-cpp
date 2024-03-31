#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT eth
   {
   public:
      virtual ~eth() = default;

      /**
       * @brief Returns accounts list.
       * @return Vec<H160>
       */
      virtual Vec<H160> eth_accounts() = 0;

      /**
       * @brief Returns the blockNumber
       * @return U256
       */
      virtual U256 eth_blockNumber() = 0;

      /**
       * @brief Call contract, returning the output data.
       * @param request EthCallRequest
       * @param number BlockNumber
       * @return Bytes
       */
      virtual Bytes eth_call(EthCallRequest request, BlockNumber number = {}) = 0;

      /**
       * @brief Returns the chain ID used for transaction signing at the current best block. None is returned if not available.
       * @return U64
       */
      virtual U64 eth_chainId() = 0;

      /**
       * @brief Returns block author.
       * @return H160
       */
      virtual H160 eth_coinbase() = 0;

      /**
       * @brief Estimate gas needed for execution of given contract.
       * @param request EthCallRequest
       * @param number BlockNumber
       * @return U256
       */
      virtual U256 eth_estimateGas(EthCallRequest request, BlockNumber number = {}) = 0;

      /**
       * @brief Returns fee history for given block count & reward percentiles
       * @param blockCount U256
       * @param newestBlock BlockNumber
       * @param rewardPercentiles Option<Vec<f64>>
       * @return EthFeeHistory
       */
      virtual EthFeeHistory eth_feeHistory(U256 blockCount, BlockNumber newestBlock, Option<Vec<f64>> rewardPercentiles) = 0;

      /**
       * @brief Returns current gas price.
       * @return U256
       */
      virtual U256 eth_gasPrice() = 0;

      /**
       * @brief Returns balance of the given account.
       * @param address H160
       * @param number BlockNumber
       * @return U256
       */
      virtual U256 eth_getBalance(H160 address, BlockNumber number = {}) = 0;

      /**
       * @brief Returns block with given hash.
       * @param hash H256
       * @param full bool
       * @return Option<EthRichBlock>
       */
      virtual Option<EthRichBlock> eth_getBlockByHash(H256 hash, bool full) = 0;

      /**
       * @brief Returns block with given number.
       * @param block BlockNumber
       * @param full bool
       * @return Option<EthRichBlock>
       */
      virtual Option<EthRichBlock> eth_getBlockByNumber(BlockNumber block, bool full) = 0;

      /**
       * @brief Returns the number of transactions in a block with given hash.
       * @param hash H256
       * @return U256
       */
      virtual U256 eth_getBlockTransactionCountByHash(H256 hash) = 0;

      /**
       * @brief Returns the number of transactions in a block with given block number.
       * @param block BlockNumber
       * @return U256
       */
      virtual U256 eth_getBlockTransactionCountByNumber(BlockNumber block) = 0;

      /**
       * @brief Returns the code at given address at given time (block number).
       * @param address H160
       * @param number BlockNumber
       * @return Bytes
       */
      virtual Bytes eth_getCode(H160 address, BlockNumber number = {}) = 0;

      /**
       * @brief Returns filter changes since last poll.
       * @param index U256
       * @return EthFilterChanges
       */
      virtual EthFilterChanges eth_getFilterChanges(U256 index) = 0;

      /**
       * @brief Returns all logs matching given filter (in a range 'from' - 'to').
       * @param index U256
       * @return Vec<EthLog>
       */
      virtual Vec<EthLog> eth_getFilterLogs(U256 index) = 0;

      /**
       * @brief Returns logs matching given filter object.
       * @param filter EthFilter
       * @return Vec<EthLog>
       */
      virtual Vec<EthLog> eth_getLogs(EthFilter filter) = 0;

      /**
       * @brief Returns proof for account and storage.
       * @param address H160
       * @param storageKeys Vec<H256>
       * @param number BlockNumber
       * @return EthAccount
       */
      virtual EthAccount eth_getProof(H160 address, Vec<H256> storageKeys, BlockNumber number) = 0;

      /**
       * @brief Returns content of the storage at given address.
       * @param address H160
       * @param index U256
       * @param number BlockNumber
       * @return H256
       */
      virtual H256 eth_getStorageAt(H160 address, U256 index, BlockNumber number = {}) = 0;

      /**
       * @brief Returns transaction at given block hash and index.
       * @param hash H256
       * @param index U256
       * @return EthTransaction
       */
      virtual EthTransaction eth_getTransactionByBlockHashAndIndex(H256 hash, U256 index) = 0;

      /**
       * @brief Returns transaction by given block number and index.
       * @param number BlockNumber
       * @param index U256
       * @return EthTransaction
       */
      virtual EthTransaction eth_getTransactionByBlockNumberAndIndex(BlockNumber number, U256 index) = 0;

      /**
       * @brief Get transaction by its hash.
       * @param hash H256
       * @return EthTransaction
       */
      virtual EthTransaction eth_getTransactionByHash(H256 hash) = 0;

      /**
       * @brief Returns the number of transactions sent from given address at given time (block number).
       * @param address H160
       * @param number BlockNumber
       * @return U256
       */
      virtual U256 eth_getTransactionCount(H160 address, BlockNumber number = {}) = 0;

      /**
       * @brief Returns transaction receipt by transaction hash.
       * @param hash H256
       * @return EthReceipt
       */
      virtual EthReceipt eth_getTransactionReceipt(H256 hash) = 0;

      /**
       * @brief Returns an uncles at given block and index.
       * @param hash H256
       * @param index U256
       * @return EthRichBlock
       */
      virtual EthRichBlock eth_getUncleByBlockHashAndIndex(H256 hash, U256 index) = 0;

      /**
       * @brief Returns an uncles at given block and index.
       * @param number BlockNumber
       * @param index U256
       * @return EthRichBlock
       */
      virtual EthRichBlock eth_getUncleByBlockNumberAndIndex(BlockNumber number, U256 index) = 0;

      /**
       * @brief Returns the number of uncles in a block with given hash.
       * @param hash H256
       * @return U256
       */
      virtual U256 eth_getUncleCountByBlockHash(H256 hash) = 0;

      /**
       * @brief Returns the number of uncles in a block with given block number.
       * @param number BlockNumber
       * @return U256
       */
      virtual U256 eth_getUncleCountByBlockNumber(BlockNumber number) = 0;

      /**
       * @brief Returns the hash of the current block, the seedHash, and the boundary condition to be met.
       * @return EthWork
       */
      virtual EthWork eth_getWork() = 0;

      /**
       * @brief Returns the number of hashes per second that the node is mining with.
       * @return U256
       */
      virtual U256 eth_hashrate() = 0;

      /**
       * @brief Returns max priority fee per gas
       * @return U256
       */
      virtual U256 eth_maxPriorityFeePerGas() = 0;

      /**
       * @brief Returns true if client is actively mining new blocks.
       * @return bool
       */
      virtual bool eth_mining() = 0;

      /**
       * @brief Returns id of new block filter.
       * @return U256
       */
      virtual U256 eth_newBlockFilter() = 0;

      /**
       * @brief Returns id of new filter.
       * @param filter EthFilter
       * @return U256
       */
      virtual U256 eth_newFilter(EthFilter filter) = 0;

      /**
       * @brief Returns id of new block filter.
       * @return U256
       */
      virtual U256 eth_newPendingTransactionFilter() = 0;

      /**
       * @brief Returns protocol version encoded as a string (quotes are necessary).
       * @return u64
       */
      virtual u64 eth_protocolVersion() = 0;

      /**
       * @brief Sends signed transaction, returning its hash.
       * @param bytes Bytes
       * @return H256
       */
      virtual H256 eth_sendRawTransaction(Bytes bytes) = 0;

      /**
       * @brief Sends transaction; will block waiting for signer to return the transaction hash
       * @param tx EthTransactionRequest
       * @return H256
       */
      virtual H256 eth_sendTransaction(EthTransactionRequest tx) = 0;

      /**
       * @brief Used for submitting mining hashrate.
       * @param index U256
       * @param hash H256
       * @return bool
       */
      virtual bool eth_submitHashrate(U256 index, H256 hash) = 0;

      /**
       * @brief Used for submitting a proof-of-work solution.
       * @param nonce H64
       * @param headerHash H256
       * @param mixDigest H256
       * @return bool
       */
      virtual bool eth_submitWork(H64 nonce, H256 headerHash, H256 mixDigest) = 0;

      /**
       * @brief Subscribe to Eth subscription.
       * @param kind EthSubKind
       * @param params EthSubParams
       * @return Null
       */
      virtual Null eth_subscribe(EthSubKind kind, EthSubParams params = {}) = 0;

      /**
       * @brief Returns an object with data about the sync status or false.
       * @return EthSyncStatus
       */
      virtual EthSyncStatus eth_syncing() = 0;

      /**
       * @brief Uninstalls filter.
       * @param index U256
       * @return bool
       */
      virtual bool eth_uninstallFilter(U256 index) = 0;
   };
}
