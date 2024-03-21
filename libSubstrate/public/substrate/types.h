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

   // BasePrim<string>
   struct Hash
   {
   };

   struct Block
   {
   };

   struct BlockData
   {
   };

   // BasePrim<uint>
   using BlockNumber = uint32_t;

   struct Header
   {
   };
}
