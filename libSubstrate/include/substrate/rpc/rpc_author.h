#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT author
   {
   public:
      virtual ~author() = default;

      /**
       * @brief Returns all pending extrinsics, potentially grouped by sender
       * @return Vec<Extrinsic>
       */
      virtual Vec<Extrinsic> author_pendingExtrinsics() const = 0;

      /**
       * @brief Submit and subscribe to watch an extrinsic until unsubscribed
       * @param callback subscription_callback_t
       * @param extrinsic Extrinsic
       * @return std::string
       */
      virtual std::string author_submitAndWatchExtrinsic(subscription_callback_t callback, Extrinsic extrinsic) const = 0;

      /**
       * @brief Submit a fully formatted extrinsic for block inclusion
       * @param extrinsic Extrinsic
       * @return Hash
       */
      virtual Hash author_submitExtrinsic(Extrinsic extrinsic) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_AUTHOR
#define SUBSTRATE_IMPL_RPC_AUTHOR \
   virtual Vec<Extrinsic> author_pendingExtrinsics() const override; \
   virtual std::string author_submitAndWatchExtrinsic(subscription_callback_t callback, Extrinsic extrinsic) const override; \
   virtual Hash author_submitExtrinsic(Extrinsic extrinsic) const override;
#endif
