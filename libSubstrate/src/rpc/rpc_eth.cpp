#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

Vec<H160> substrate_client::eth_accounts() const
{
   return rpc<Vec<H160>>("eth_accounts");
}

U256 substrate_client::eth_blockNumber() const
{
   return rpc<U256>("eth_blockNumber");
}

Bytes substrate_client::eth_call(EthCallRequest request, std::optional<BlockNumber> number) const
{
   return rpc<Bytes>("eth_call", request, number);
}

U64 substrate_client::eth_chainId() const
{
   return rpc<U64>("eth_chainId");
}

H160 substrate_client::eth_coinbase() const
{
   return rpc<H160>("eth_coinbase");
}

U256 substrate_client::eth_estimateGas(EthCallRequest request, std::optional<BlockNumber> number) const
{
   return rpc<U256>("eth_estimateGas", request, number);
}

EthFeeHistory substrate_client::eth_feeHistory(U256 blockCount, BlockNumber newestBlock, Option<Vec<f64>> rewardPercentiles) const
{
   return rpc<EthFeeHistory>("eth_feeHistory", blockCount, newestBlock, rewardPercentiles);
}

U256 substrate_client::eth_gasPrice() const
{
   return rpc<U256>("eth_gasPrice");
}

U256 substrate_client::eth_getBalance(H160 address, std::optional<BlockNumber> number) const
{
   return rpc<U256>("eth_getBalance", address, number);
}

Option<EthRichBlock> substrate_client::eth_getBlockByHash(H256 hash, bool full) const
{
   return rpc<Option<EthRichBlock>>("eth_getBlockByHash", hash, full);
}

Option<EthRichBlock> substrate_client::eth_getBlockByNumber(BlockNumber block, bool full) const
{
   return rpc<Option<EthRichBlock>>("eth_getBlockByNumber", block, full);
}

U256 substrate_client::eth_getBlockTransactionCountByHash(H256 hash) const
{
   return rpc<U256>("eth_getBlockTransactionCountByHash", hash);
}

U256 substrate_client::eth_getBlockTransactionCountByNumber(BlockNumber block) const
{
   return rpc<U256>("eth_getBlockTransactionCountByNumber", block);
}

Bytes substrate_client::eth_getCode(H160 address, std::optional<BlockNumber> number) const
{
   return rpc<Bytes>("eth_getCode", address, number);
}

EthFilterChanges substrate_client::eth_getFilterChanges(U256 index) const
{
   return rpc<EthFilterChanges>("eth_getFilterChanges", index);
}

Vec<EthLog> substrate_client::eth_getFilterLogs(U256 index) const
{
   return rpc<Vec<EthLog>>("eth_getFilterLogs", index);
}

Vec<EthLog> substrate_client::eth_getLogs(EthFilter filter) const
{
   return rpc<Vec<EthLog>>("eth_getLogs", filter);
}

EthAccount substrate_client::eth_getProof(H160 address, Vec<H256> storageKeys, BlockNumber number) const
{
   return rpc<EthAccount>("eth_getProof", address, storageKeys, number);
}

H256 substrate_client::eth_getStorageAt(H160 address, U256 index, std::optional<BlockNumber> number) const
{
   return rpc<H256>("eth_getStorageAt", address, index, number);
}

EthTransaction substrate_client::eth_getTransactionByBlockHashAndIndex(H256 hash, U256 index) const
{
   return rpc<EthTransaction>("eth_getTransactionByBlockHashAndIndex", hash, index);
}

EthTransaction substrate_client::eth_getTransactionByBlockNumberAndIndex(BlockNumber number, U256 index) const
{
   return rpc<EthTransaction>("eth_getTransactionByBlockNumberAndIndex", number, index);
}

EthTransaction substrate_client::eth_getTransactionByHash(H256 hash) const
{
   return rpc<EthTransaction>("eth_getTransactionByHash", hash);
}

U256 substrate_client::eth_getTransactionCount(H160 address, std::optional<BlockNumber> number) const
{
   return rpc<U256>("eth_getTransactionCount", address, number);
}

EthReceipt substrate_client::eth_getTransactionReceipt(H256 hash) const
{
   return rpc<EthReceipt>("eth_getTransactionReceipt", hash);
}

EthRichBlock substrate_client::eth_getUncleByBlockHashAndIndex(H256 hash, U256 index) const
{
   return rpc<EthRichBlock>("eth_getUncleByBlockHashAndIndex", hash, index);
}

EthRichBlock substrate_client::eth_getUncleByBlockNumberAndIndex(BlockNumber number, U256 index) const
{
   return rpc<EthRichBlock>("eth_getUncleByBlockNumberAndIndex", number, index);
}

U256 substrate_client::eth_getUncleCountByBlockHash(H256 hash) const
{
   return rpc<U256>("eth_getUncleCountByBlockHash", hash);
}

U256 substrate_client::eth_getUncleCountByBlockNumber(BlockNumber number) const
{
   return rpc<U256>("eth_getUncleCountByBlockNumber", number);
}

EthWork substrate_client::eth_getWork() const
{
   return rpc<EthWork>("eth_getWork");
}

U256 substrate_client::eth_hashrate() const
{
   return rpc<U256>("eth_hashrate");
}

U256 substrate_client::eth_maxPriorityFeePerGas() const
{
   return rpc<U256>("eth_maxPriorityFeePerGas");
}

bool substrate_client::eth_mining() const
{
   return rpc<bool>("eth_mining");
}

U256 substrate_client::eth_newBlockFilter() const
{
   return rpc<U256>("eth_newBlockFilter");
}

U256 substrate_client::eth_newFilter(EthFilter filter) const
{
   return rpc<U256>("eth_newFilter", filter);
}

U256 substrate_client::eth_newPendingTransactionFilter() const
{
   return rpc<U256>("eth_newPendingTransactionFilter");
}

u64 substrate_client::eth_protocolVersion() const
{
   return rpc<u64>("eth_protocolVersion");
}

H256 substrate_client::eth_sendRawTransaction(Bytes bytes) const
{
   return rpc<H256>("eth_sendRawTransaction", bytes);
}

H256 substrate_client::eth_sendTransaction(EthTransactionRequest tx) const
{
   return rpc<H256>("eth_sendTransaction", tx);
}

bool substrate_client::eth_submitHashrate(U256 index, H256 hash) const
{
   return rpc<bool>("eth_submitHashrate", index, hash);
}

bool substrate_client::eth_submitWork(H64 nonce, H256 headerHash, H256 mixDigest) const
{
   return rpc<bool>("eth_submitWork", nonce, headerHash, mixDigest);
}

Null substrate_client::eth_subscribe(EthSubKind kind, std::optional<EthSubParams> params) const
{
   return rpc<Null>("eth_subscribe", kind, params);
}

EthSyncStatus substrate_client::eth_syncing() const
{
   return rpc<EthSyncStatus>("eth_syncing");
}

bool substrate_client::eth_uninstallFilter(U256 index) const
{
   return rpc<bool>("eth_uninstallFilter", index);
}

