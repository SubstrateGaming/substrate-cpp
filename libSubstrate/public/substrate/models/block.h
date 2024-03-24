#pragma once
#include "extrinsic.h"
#include "header.h"

namespace substrate::models
{
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

LIB_SUBSTRATE_EXPORT substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::BlockNumber& v);
LIB_SUBSTRATE_EXPORT substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::BlockNumber& v);
