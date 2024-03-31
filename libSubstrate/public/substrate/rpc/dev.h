#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT dev
   {
   public:
      virtual ~dev() = default;

      /**
       * @brief Reexecute the specified block_hash and gather statistics while doing so
       * @warning This method is marked as unsafe.
       * @param at Hash
       * @return Option<BlockStats>
       */
      virtual Option<BlockStats> dev_getBlockStats(Hash at) = 0;
   };
}
