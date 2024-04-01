#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>
#include <optional>
#include <unordered_map>

#include <boost/multiprecision/cpp_int.hpp>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class LIB_SUBSTRATE_EXPORT IClient;
   using Client = std::shared_ptr<IClient>;

   class LIB_SUBSTRATE_EXPORT ICrypto;
   using Crypto = std::shared_ptr<ICrypto>;

   using bytes = std::vector<uint8_t>;
   using CompactInteger = boost::multiprecision::cpp_int;

   template <typename T, typename Tag, size_t TypeSize = sizeof(T)>
   class strong_type
   {
      T _value;
   public:
      explicit constexpr strong_type(T v) : _value(v) {}
      constexpr strong_type() : _value(T()) {}
      explicit operator T() const { return _value; }
      T value() const { return _value; }

      static size_t GetTypeSize() { return TypeSize; }
   };

   namespace constants
   {
      /// <summary>
      /// The address version
      ///  https://polkadot.js.org/docs/api/FAQ/
      ///  0 = AccountId (no prefix), 1 = IndicesLookup (0xFF), 2 = MutiAddress (https://github.com/paritytech/substrate/pull/7380)
      /// </summary>
      constexpr const uint32_t AddressVersion = 2;

      // https://github.com/paritytech/substrate/blob/c0cb70419798eb7fd38806da668bec05f8cfd7f1/primitives/runtime/src/generic/unchecked_extrinsic.rs#L33
      // aka TRANSACTION_VERSION
      constexpr const uint8_t TransactionVersion = 4;
   }

   namespace rpc
   {
      using Bytes = substrate::bytes;
      using Text = std::string;

      template<typename T>
      using Vec = std::vector<T>;

      template <typename K, typename V>
      using HashMap = std::unordered_map<K, V>;

      // TODO: Verify if that is even correct.
      template <typename T>
      using Option = std::optional<T>;

      // TODO:
      using ExtrinsicOrHash = Bytes;
      using ExtrinsicStatus = Bytes;
      using AuthorityId = int32_t;
      using EpochAuthorship = int32_t;
      using H160 = Bytes;
      using H256 = Bytes;
      using H64 = Bytes;
      using BeefyVersionedFinalityProof = Bytes;
      using StorageKey = Bytes;
      using PrefixedStorageKey = Bytes;
      using StorageData = Bytes;
      using ContractExecResult = Bytes;
      using ContractCallRequest = Bytes;
      using ContractInstantiateResult = Bytes;
      using InstantiateRequestV1 = Bytes;
      using CodeUploadRequest = Bytes;
      using CodeUploadResult = Bytes;
      using BlockStats = Bytes;
      using CreatedBlock = Bytes;
      using Justification = Bytes;
      using EthCallRequest = Bytes;
      using EthFeeHistory = Bytes;
      using EthRichBlock = Bytes;
      using EthFilterChanges = Bytes;
      using EthLog = Bytes;
      using EthFilter = Bytes;
      using EthAccount = Bytes;
      using EthTransaction = Bytes;
      using EthReceipt = Bytes;
      using EthRichBlock = Bytes;
      using EthWork = Bytes;
      using EthTransactionRequest = Bytes;
      using EthSyncStatus = Bytes;
      using Null = Bytes;
      using EthSubKind = Bytes;
      using EthSubParams = Bytes;
      using f64 = Bytes;
      using u32 = uint32_t;
      using u64 = uint64_t;
      using U256 = CompactInteger;
      using U64 = u64;
      using MmrLeafBatchProof = Bytes;
      using MmrHash = Bytes;
      using EncodedFinalityProofs = Bytes;
      using ReportedRoundStates = Bytes;
      using JustificationNotification = Bytes;
      using StorageKind = Bytes;
      using FeeDetails = Bytes;
      using RuntimeDispatchInfoV1 = Bytes;
      using RpcMethods = Bytes;
      using ReadProof = Bytes;
      using KeyValue = Bytes;
      using StorageChangeSet = Bytes;
      using Metadata = Bytes;
      using TraceBlockResponse = Bytes;
      using MigrationStatusResult = Bytes;
      using Json = Bytes;
      using Index = Bytes;
      using ChainType = Bytes;
      using ApplyExtrinsicResult = Bytes;
      using Health = Bytes;
      using NetworkState = Bytes;
      using NodeRole = Bytes;
      using PeerInfo = Bytes;
      using ChainProperties = Bytes;
      using SyncState = Bytes;
   }
}
