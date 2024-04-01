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
      virtual Option<BlockStats> dev_getBlockStats(Hash at) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_DEV
#define SUBSTRATE_IMPL_RPC_DEV \
   virtual Option<BlockStats> dev_getBlockStats(Hash at) const override;
#endif
