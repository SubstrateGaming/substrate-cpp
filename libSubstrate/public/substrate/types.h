#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>
#include <optional>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class LIB_SUBSTRATE_EXPORT IClient;
   using Client = std::shared_ptr<IClient>;

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

   struct Block
   {
   };

   struct BlockData
   {
   };

   struct BlockNumberTag { };
   struct BlockNumber : strong_type<uint32_t, BlockNumberTag>
   {
      using strong_type::strong_type;
   };
   static_assert(sizeof(BlockNumber) == sizeof(uint32_t), "BlockNumber must be the same size as uint32_t");

   struct Header
   {
   };
}
