#pragma once
#include "types.h"

#include <nlohmann/json.hpp>

#ifndef LIB_SUBSTRATE_DECLARE_CONVERT_JSON
#define LIB_SUBSTRATE_DECLARE_CONVERT_JSON(type) \
   LIB_SUBSTRATE_EXPORT void to_json(nlohmann::json &j, const type &v); \
   LIB_SUBSTRATE_EXPORT void from_json(const nlohmann::json &j, type &v);
#endif

#ifndef LIB_SUBSTRATE_DECLARE_CONVERT_SCALE
#define LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(type) \
   LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const type& v); \
   LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, type& v);
#endif

#ifndef LIB_SUBSTRATE_DECLARE_CONVERT
#define LIB_SUBSTRATE_DECLARE_CONVERT(type) \
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(type) \
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(type)
#endif

namespace substrate::rpc
{
   using Bytes = substrate::bytes;
   using Text = std::string;
   using Index = CompactInteger;

   template<typename T>
   using Vec = std::vector<T>;

   template <typename K, typename V>
   using HashMap = std::unordered_map<K, V>;

   // TODO: Verify if that is even correct.
   template <typename T>
   using Option = std::optional<T>;

   // KeyType
   // https://github.com/paritytech/substrate/blob/8bc45ed4be61b83dcfac77bfc8002858ff8042ec/primitives/runtime/src/lib.rs#L230L240
   enum class KeyType
   {
      Unknown  = -1,

      /// Ed22519 signature
      Ed25519  = 0,

      /// Sr25519 signature
      Sr25519  = 1,

      /// ECDSA/SECP256k1 signature
      Ecdsa    = 2
   };

   // Hash
   struct HashTag { };
   struct Hash : strong_type<std::string, HashTag, 32>
   {
      using strong_type::strong_type;
   };
   using BlockHash = Hash;
   LIB_SUBSTRATE_DECLARE_CONVERT(Hash);

   // AccountId
   struct AccountIdTag { };
   struct AccountId : strong_type<std::string, AccountIdTag, 32>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(AccountId);

   // Digest
   struct Digest
   {
      std::vector<std::string> Logs;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Digest);

   // Header
   struct Header
   {
      Digest Digest;
      Hash ExtrinsicsRoot;
      uint64_t Number{0};
      Hash ParentHash;
      Hash StateRoot;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Header);

   // Charge Type
   struct ChargeTypeBase { };
   struct ChargeAssetTxPayment : ChargeTypeBase
   {
      substrate::CompactInteger Tip;
      substrate::CompactInteger AssetId;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(ChargeAssetTxPayment);

   struct ChargeTransactionPayment : ChargeTypeBase
   {
      substrate::CompactInteger Tip;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(ChargeTransactionPayment);

   // TODO: Make the ChargeType templated for Extrinsic type.
   using ChargeType = ChargeAssetTxPayment;

   struct Signature
   {
      KeyType Type{0};
      substrate::bytes Bytes;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Signature);

   // Era
   struct Era
   {
      bool IsImmortal{false};
      uint64_t Period{0};
      uint64_t Phase{0};

      uint64_t get_start(uint64_t blockNumber) const;
      static Era make(uint32_t lifeTime, uint64_t finalizedHeaderBlockNumber);
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Era);

   // Method
   struct Method
   {
      uint8_t ModuleIndex{0};
      uint8_t CallIndex{0};
      substrate::bytes Parameters;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Method);

   // Extrinsic
   struct Extrinsic
   {
      bool Signed{false};
      uint8_t TransactionVersion{0};
      AccountId Account;
      Era Era;
      Index Nonce;
      ChargeType Charge;
      Method Method;
      Signature Signature;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Extrinsic);

   // Block
   struct Block
   {
      std::vector<Extrinsic> Extrinsics;
      Header Header;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Block);

   // BlockNumber
   struct BlockNumberTag { };
   struct BlockNumber : strong_type<uint32_t, BlockNumberTag>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(BlockNumber);
   static_assert(sizeof(BlockNumber) == sizeof(uint32_t), "BlockNumber must be the same size as uint32_t");

   // SignedBlock
   struct SignedBlock
   {
      Block Block;
      substrate::bytes Justification;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(SignedBlock);

   // RuntimeVersion
   struct RuntimeVersion
   {
      uint32_t AuthoringVersion{0};
      uint32_t ImplVersion{0};
      uint32_t SpecVersion{0};
      uint32_t TransactionVersion{0};
      std::string ImplName;
      std::string SpecName;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(RuntimeVersion);

   // Payload
   struct Payload
   {
      struct extra_t
      {
         Era Mortality;
         CompactInteger Nonce;
         ChargeType Charge;
      };

      struct additional_t
      {
         uint32_t SpecVersion;
         uint32_t TransactionVersion;
         Hash GenesisHash;
         // Immortal: Use Genesis Hash
         //           otherwise use StartEra
         Hash CheckpointHash;
      };

      Method Call;
      extra_t Extra;
      additional_t Additional;

      static Payload make(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion);
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload::extra_t);
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload::additional_t);
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload);

   LIB_SUBSTRATE_EXPORT void to_json(nlohmann::json &j, const Bytes &p);
   LIB_SUBSTRATE_EXPORT void from_json(const nlohmann::json &j, Bytes &p);

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
   using ChainType = Bytes;
   using ApplyExtrinsicResult = Bytes;
   using Health = Bytes;
   using NetworkState = Bytes;
   using NodeRole = Bytes;
   using PeerInfo = Bytes;
   using ChainProperties = Bytes;
   using SyncState = Bytes;
}
