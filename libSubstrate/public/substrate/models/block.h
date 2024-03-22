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
