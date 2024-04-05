#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT system
   {
   public:
      virtual ~system() = default;

      /**
       * @brief Retrieves the next accountIndex as available on the node
       * @param accountId AccountId
       * @return Index
       */
      virtual Index system_accountNextIndex(AccountId accountId) const = 0;

      /**
       * @brief Retrieves the chain
       * @return Text
       */
      virtual Text system_chain() const = 0;

      /**
       * @brief Retrieves the chain type
       * @return ChainType
       */
      virtual ChainType system_chainType() const = 0;

      /**
       * @brief Return health status of the node
       * @return Health
       */
      virtual Health system_health() const = 0;

      /**
       * @brief The addresses include a trailing /p2p/ with the local PeerId, and are thus suitable to be passed to addReservedPeer or as a bootnode address for example
       * @return Vec<Text>
       */
      virtual Vec<Text> system_localListenAddresses() const = 0;

      /**
       * @brief Returns the base58-encoded PeerId of the node
       * @return Text
       */
      virtual Text system_localPeerId() const = 0;

      /**
       * @brief Retrieves the node name
       * @return Text
       */
      virtual Text system_name() const = 0;

      /**
       * @brief Returns the roles the node is running as
       * @return Vec<NodeRole>
       */
      virtual Vec<NodeRole> system_nodeRoles() const = 0;

      /**
       * @brief Get a custom set of properties as a JSON object, defined in the chain spec
       * @return ChainProperties
       */
      virtual ChainProperties system_properties() const = 0;

      /**
       * @brief Returns the list of reserved peers
       * @return Vec<Text>
       */
      virtual Vec<Text> system_reservedPeers() const = 0;

      /**
       * @brief Returns the state of the syncing of the node
       * @return SyncState
       */
      virtual SyncState system_syncState() const = 0;

      /**
       * @brief Retrieves the version of the node
       * @return Text
       */
      virtual Text system_version() const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_SYSTEM
#define SUBSTRATE_IMPL_RPC_SYSTEM \
   virtual Index system_accountNextIndex(AccountId accountId) const override; \
   virtual Text system_chain() const override; \
   virtual ChainType system_chainType() const override; \
   virtual Health system_health() const override; \
   virtual Vec<Text> system_localListenAddresses() const override; \
   virtual Text system_localPeerId() const override; \
   virtual Text system_name() const override; \
   virtual Vec<NodeRole> system_nodeRoles() const override; \
   virtual ChainProperties system_properties() const override; \
   virtual Vec<Text> system_reservedPeers() const override; \
   virtual SyncState system_syncState() const override; \
   virtual Text system_version() const override;
#endif
