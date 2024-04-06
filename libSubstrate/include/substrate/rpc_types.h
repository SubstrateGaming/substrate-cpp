#pragma once
#include "types.h"

#include <functional>
#include <nlohmann/json.hpp>

#ifndef LIB_SUBSTRATE_DECLARE_CONVERT_JSON
#define LIB_SUBSTRATE_DECLARE_CONVERT_JSON(type) \
   LIB_SUBSTRATE_EXPORT void to_json(nlohmann::json &j, const type &v); \
   LIB_SUBSTRATE_EXPORT void from_json(const nlohmann::json &j, type &v);
#endif

#ifndef LIB_SUBSTRATE_DECLARE_CONVERT_JSON_OPTIONAL
#define LIB_SUBSTRATE_DECLARE_CONVERT_JSON_OPTIONAL(type) \
   LIB_SUBSTRATE_EXPORT void to_json(nlohmann::json &j, const std::optional<type> &v); \
   LIB_SUBSTRATE_EXPORT void from_json(const nlohmann::json &j, std::optional<type> &v);
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
   using u32 = uint32_t;
   using u64 = uint64_t;

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

   struct BytesTag { };
   struct Bytes : strong_type<substrate::bytes, BytesTag, 0>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(Bytes);

   // Hash
   struct HashTag { };
   struct Hash : strong_type<std::string, HashTag, 32>
   {
      using strong_type::strong_type;
   };
   using BlockHash = Hash;
   LIB_SUBSTRATE_DECLARE_CONVERT(Hash);

   // StorageKey
   struct StorageKeyTag { };
   struct StorageKey : strong_type<std::string, StorageKeyTag, 0>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(StorageKey);

   // StorageData
   struct StorageDataTag { };
   struct StorageData : strong_type<std::string, StorageDataTag, 0>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT(StorageData);

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
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(Digest);

   // Header
   struct Header
   {
      Digest digest;
      Hash extrinsicsRoot;
      CompactInteger number{0};
      Hash parentHash;
      Hash stateRoot;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(Header);

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

      [[nodiscard]] LIB_SUBSTRATE_EXPORT uint64_t get_start(uint64_t blockNumber) const;
      [[nodiscard]] static LIB_SUBSTRATE_EXPORT Era make(uint32_t lifeTime, CompactInteger finalizedHeaderBlockNumber);
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
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(Block);

   // BlockNumber
   struct BlockNumberTag { };
   struct BlockNumber : strong_type<uint32_t, BlockNumberTag>
   {
      using strong_type::strong_type;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(BlockNumber);
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON_OPTIONAL(BlockNumber);
   static_assert(sizeof(BlockNumber) == sizeof(uint32_t), "BlockNumber must be the same size as uint32_t");

   // Not really sure. Should be a tuple but have seen different things during development.
   // Not really needing this yet so we simply pass the default type to at least allow custom parsing.
   using Justification = nlohmann::json;

   // SignedBlock
   struct SignedBlock
   {
      Block Block;
      std::optional<std::vector<Justification>> Justifications;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(SignedBlock);

   // RuntimeVersion
   struct RuntimeVersion
   {
      uint32_t authoringVersion{0};
      uint32_t implVersion{0};
      uint32_t specVersion{0};
      uint32_t transactionVersion{0};
      std::string implName;
      std::string specName;
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
         Hash CheckpointHash;
      };

      Method Call;
      extra_t Extra;
      additional_t Additional;

      [[nodiscard]] static LIB_SUBSTRATE_EXPORT Payload make(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion);
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload::extra_t);
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload::additional_t);
   LIB_SUBSTRATE_DECLARE_CONVERT_SCALE(Payload);

   struct Health
   {
      u64 peers{0};
      bool isSyncing{false};
      bool shouldHavePeers{false};
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(Health);

   struct SyncState
   {
      BlockNumber startingBlock{0};
      BlockNumber currentBlock{0};
      std::optional<BlockNumber> highestBlock;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(SyncState);

   // The PolkadotJs type is different, but I have not yet seen any other encoding of that from the RPC.
   // So we use the text encoded variant at this time.
   using NodeRole = Text;

   // Is different depending on chain.
   // We simply provide the raw object once the chain properties are queried.
   // Users of this API should know what they're looking for in the properties.
   using ChainProperties = nlohmann::json;

   using Balance = CompactInteger;

   struct InclusionFee
   {
      Balance baseFee;
      Balance lenFee;
      Balance adjustedWeightFee;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(InclusionFee);

   struct FeeDetails
   {
      std::optional<InclusionFee> inclusionFee;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(FeeDetails);

   struct RuntimeDispatchInfoV1
   {
      struct Weight
      {
         uint32_t ref_time{0};
         uint32_t proof_size{0};
      };

      Weight weight;
      std::string classz;

      // Is a large number but really encoded as string.
      std::string partialFee;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(RuntimeDispatchInfoV1::Weight);
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(RuntimeDispatchInfoV1);

   struct StorageChangeSet
   {
      Hash block;
      Vec<Vec<Text>> changes;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(StorageChangeSet);

   struct ReadProof
   {
      Hash at;
      Vec<Hash> proof;
   };
   LIB_SUBSTRATE_DECLARE_CONVERT_JSON(ReadProof);

   // There is no need for now to parse the metadata in C++.
   // We can still use the .NET API for that as the SDK generators are in .NET aswell.
   // If needed, we must define all the structs here and scale decoders.
   using Metadata = std::string;

   // Susbcription Callbacks
   using subscription_callback_t = std::function<void(const nlohmann::json&)>;

   // TODO:
   using ExtrinsicOrHash = Bytes;
   using ExtrinsicStatus = Bytes;
   using PrefixedStorageKey = Bytes;
   using Null = Bytes;
   using RpcMethods = Bytes;
   using KeyValue = Bytes;
   using TraceBlockResponse = Bytes;
   using MigrationStatusResult = Bytes;
   using ChainType = Bytes;
   using ApplyExtrinsicResult = Bytes;
   using NetworkState = Bytes;

   using PeerInfo = Bytes;

   LIB_SUBSTRATE_EXPORT void to_json(nlohmann::json &j, const CompactInteger &p);
   LIB_SUBSTRATE_EXPORT void from_json(const nlohmann::json &j, CompactInteger &p);
}
