#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT syncstate
   {
   public:
      virtual ~syncstate() = default;

      /**
       * @brief Returns the json-serialized chainspec running the node, with a sync state.
       * @param raw bool
       * @return Json
       */
      virtual Json sync_state_genSyncSpec(bool raw) = 0;
   };
}
