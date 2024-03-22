#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>
#include <optional>

#include <boost/multiprecision/cpp_int.hpp>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class LIB_SUBSTRATE_EXPORT IClient;
   using Client = std::shared_ptr<IClient>;

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

   // BasePrim<string>
   struct HashTag { };
   struct Hash : strong_type<std::string, HashTag, 32>
   {
      using strong_type::strong_type;
   };

   struct AccountIdTag { };
   struct AccountId : strong_type<std::string, AccountIdTag, 32>
   {
      using strong_type::strong_type;
   };

   enum class KeyType
   {
      Unknown  = -1,
      Ed25519  = 0,
      Sr25519  = 1
   };

   struct Account : AccountId
   {
      KeyType KeyType{KeyType::Unknown};
      std::vector<uint8_t> PrivateKey;
   };

   struct Era
   {
      bool IsImmortal{false};
      uint64_t Period{0};
      uint64_t Phase{0};
   };

   struct Digest
   {
      std::vector<std::string> Logs;
   };

   struct ChargeType
   {
   };

   struct Method
   {
      std::string ModuleName;
      uint8_t ModuleIndex{0};
      std::string CallName;
      uint8_t CallIndex{0};
      std::vector<uint8_t> Parameters;
   };

   struct Extrinsic
   {
      bool Signed{false};
      uint8_t TransactionVersion{0};
      Account Account;
      Era Era;
      CompactInteger Nonce;
      ChargeType Charge;
      Method Method;
      std::vector<uint8_t> Signature;
   };

   struct Header
   {
      Digest Digest;
      Hash ExtrinsicsRoot;
      uint64_t Number{0};
      Hash ParentHash;
      Hash StateRoot;
   };

   struct Block
   {
      std::vector<Extrinsic> Extrinsics;
      Header Header;
   };

   struct BlockData
   {
      Block Block;
      std::vector<uint8_t> Justification;
   };

   struct BlockNumberTag { };
   struct BlockNumber : strong_type<uint32_t, BlockNumberTag>
   {
      using strong_type::strong_type;
   };
   static_assert(sizeof(BlockNumber) == sizeof(uint32_t), "BlockNumber must be the same size as uint32_t");
}
