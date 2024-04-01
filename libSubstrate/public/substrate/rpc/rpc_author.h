#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT author
   {
   public:
      virtual ~author() = default;

      /**
       * @brief Returns true if the keystore has private keys for the given public key and key type.
       * @warning This method is marked as unsafe.
       * @param publicKey Bytes
       * @param keyType Text
       * @return bool
       */
      virtual bool author_hasKey(Bytes publicKey, Text keyType) const = 0;

      /**
       * @brief Returns true if the keystore has private keys for the given session public keys.
       * @warning This method is marked as unsafe.
       * @param sessionKeys Bytes
       * @return bool
       */
      virtual bool author_hasSessionKeys(Bytes sessionKeys) const = 0;

      /**
       * @brief Insert a key into the keystore.
       * @warning This method is marked as unsafe.
       * @param keyType Text
       * @param suri Text
       * @param publicKey Bytes
       * @return Bytes
       */
      virtual Bytes author_insertKey(Text keyType, Text suri, Bytes publicKey) const = 0;

      /**
       * @brief Returns all pending extrinsics, potentially grouped by sender
       * @return Vec<Extrinsic>
       */
      virtual Vec<Extrinsic> author_pendingExtrinsics() const = 0;

      /**
       * @brief Remove given extrinsic from the pool and temporarily ban it to prevent reimporting
       * @warning This method is marked as unsafe.
       * @param bytesOrHash Vec<ExtrinsicOrHash>
       * @return Vec<Hash>
       */
      virtual Vec<Hash> author_removeExtrinsic(Vec<ExtrinsicOrHash> bytesOrHash) const = 0;

      /**
       * @brief Generate new session keys and returns the corresponding public keys
       * @warning This method is marked as unsafe.
       * @return Bytes
       */
      virtual Bytes author_rotateKeys() const = 0;

      /**
       * @brief Submit and subscribe to watch an extrinsic until unsubscribed
       * @param extrinsic Extrinsic
       * @return ExtrinsicStatus
       */
      virtual ExtrinsicStatus author_submitAndWatchExtrinsic(Extrinsic extrinsic) const = 0;

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
   virtual bool author_hasKey(Bytes publicKey, Text keyType) const override; \
   virtual bool author_hasSessionKeys(Bytes sessionKeys) const override; \
   virtual Bytes author_insertKey(Text keyType, Text suri, Bytes publicKey) const override; \
   virtual Vec<Extrinsic> author_pendingExtrinsics() const override; \
   virtual Vec<Hash> author_removeExtrinsic(Vec<ExtrinsicOrHash> bytesOrHash) const override; \
   virtual Bytes author_rotateKeys() const override; \
   virtual ExtrinsicStatus author_submitAndWatchExtrinsic(Extrinsic extrinsic) const override; \
   virtual Hash author_submitExtrinsic(Extrinsic extrinsic) const override;
#endif
