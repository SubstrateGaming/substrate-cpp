#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

Vec<H160> substrate_client::eth_accounts()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_blockNumber()
{
   throw std::runtime_error("not implemented");
}

Bytes substrate_client::eth_call(EthCallRequest request, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

U64 substrate_client::eth_chainId()
{
   throw std::runtime_error("not implemented");
}

H160 substrate_client::eth_coinbase()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_estimateGas(EthCallRequest request, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

EthFeeHistory substrate_client::eth_feeHistory(U256 blockCount, BlockNumber newestBlock, Option<Vec<f64>> rewardPercentiles)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_gasPrice()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getBalance(H160 address, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

Option<EthRichBlock> substrate_client::eth_getBlockByHash(H256 hash, bool full)
{
   throw std::runtime_error("not implemented");
}

Option<EthRichBlock> substrate_client::eth_getBlockByNumber(BlockNumber block, bool full)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getBlockTransactionCountByHash(H256 hash)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getBlockTransactionCountByNumber(BlockNumber block)
{
   throw std::runtime_error("not implemented");
}

Bytes substrate_client::eth_getCode(H160 address, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

EthFilterChanges substrate_client::eth_getFilterChanges(U256 index)
{
   throw std::runtime_error("not implemented");
}

Vec<EthLog> substrate_client::eth_getFilterLogs(U256 index)
{
   throw std::runtime_error("not implemented");
}

Vec<EthLog> substrate_client::eth_getLogs(EthFilter filter)
{
   throw std::runtime_error("not implemented");
}

EthAccount substrate_client::eth_getProof(H160 address, Vec<H256> storageKeys, BlockNumber number)
{
   throw std::runtime_error("not implemented");
}

H256 substrate_client::eth_getStorageAt(H160 address, U256 index, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

EthTransaction substrate_client::eth_getTransactionByBlockHashAndIndex(H256 hash, U256 index)
{
   throw std::runtime_error("not implemented");
}

EthTransaction substrate_client::eth_getTransactionByBlockNumberAndIndex(BlockNumber number, U256 index)
{
   throw std::runtime_error("not implemented");
}

EthTransaction substrate_client::eth_getTransactionByHash(H256 hash)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getTransactionCount(H160 address, std::optional<BlockNumber> number)
{
   throw std::runtime_error("not implemented");
}

EthReceipt substrate_client::eth_getTransactionReceipt(H256 hash)
{
   throw std::runtime_error("not implemented");
}

EthRichBlock substrate_client::eth_getUncleByBlockHashAndIndex(H256 hash, U256 index)
{
   throw std::runtime_error("not implemented");
}

EthRichBlock substrate_client::eth_getUncleByBlockNumberAndIndex(BlockNumber number, U256 index)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getUncleCountByBlockHash(H256 hash)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_getUncleCountByBlockNumber(BlockNumber number)
{
   throw std::runtime_error("not implemented");
}

EthWork substrate_client::eth_getWork()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_hashrate()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_maxPriorityFeePerGas()
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::eth_mining()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_newBlockFilter()
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_newFilter(EthFilter filter)
{
   throw std::runtime_error("not implemented");
}

U256 substrate_client::eth_newPendingTransactionFilter()
{
   throw std::runtime_error("not implemented");
}

u64 substrate_client::eth_protocolVersion()
{
   throw std::runtime_error("not implemented");
}

H256 substrate_client::eth_sendRawTransaction(Bytes bytes)
{
   throw std::runtime_error("not implemented");
}

H256 substrate_client::eth_sendTransaction(EthTransactionRequest tx)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::eth_submitHashrate(U256 index, H256 hash)
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::eth_submitWork(H64 nonce, H256 headerHash, H256 mixDigest)
{
   throw std::runtime_error("not implemented");
}

Null substrate_client::eth_subscribe(EthSubKind kind, std::optional<EthSubParams> params)
{
   throw std::runtime_error("not implemented");
}

EthSyncStatus substrate_client::eth_syncing()
{
   throw std::runtime_error("not implemented");
}

bool substrate_client::eth_uninstallFilter(U256 index)
{
   throw std::runtime_error("not implemented");
}

