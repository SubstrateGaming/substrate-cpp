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
      virtual Index system_accountNextIndex(AccountId accountId) = 0;

      /**
       * @brief Adds the supplied directives to the current log filter
       * @warning This method is marked as unsafe.
       * @param directives Text
       * @return Null
       */
      virtual Null system_addLogFilter(Text directives) = 0;

      /**
       * @brief Adds a reserved peer
       * @warning This method is marked as unsafe.
       * @param peer Text
       * @return Text
       */
      virtual Text system_addReservedPeer(Text peer) = 0;

      /**
       * @brief Retrieves the chain
       * @return Text
       */
      virtual Text system_chain() = 0;

      /**
       * @brief Retrieves the chain type
       * @return ChainType
       */
      virtual ChainType system_chainType() = 0;

      /**
       * @brief Dry run an extrinsic at a given block
       * @warning This method is marked as unsafe.
       * @param extrinsic Bytes
       * @param at BlockHash
       * @return ApplyExtrinsicResult
       */
      virtual ApplyExtrinsicResult system_dryRun(Bytes extrinsic, BlockHash at = {}) = 0;

      /**
       * @brief Return health status of the node
       * @return Health
       */
      virtual Health system_health() = 0;

      /**
       * @brief The addresses include a trailing /p2p/ with the local PeerId, and are thus suitable to be passed to addReservedPeer or as a bootnode address for example
       * @return Vec<Text>
       */
      virtual Vec<Text> system_localListenAddresses() = 0;

      /**
       * @brief Returns the base58-encoded PeerId of the node
       * @return Text
       */
      virtual Text system_localPeerId() = 0;

      /**
       * @brief Retrieves the node name
       * @return Text
       */
      virtual Text system_name() = 0;

      /**
       * @brief Returns current state of the network
       * @warning This method is marked as unsafe.
       * @return NetworkState
       */
      virtual NetworkState system_networkState() = 0;

      /**
       * @brief Returns the roles the node is running as
       * @return Vec<NodeRole>
       */
      virtual Vec<NodeRole> system_nodeRoles() = 0;

      /**
       * @brief Returns the currently connected peers
       * @warning This method is marked as unsafe.
       * @return Vec<PeerInfo>
       */
      virtual Vec<PeerInfo> system_peers() = 0;

      /**
       * @brief Get a custom set of properties as a JSON object, defined in the chain spec
       * @return ChainProperties
       */
      virtual ChainProperties system_properties() = 0;

      /**
       * @brief Remove a reserved peer
       * @warning This method is marked as unsafe.
       * @param peerId Text
       * @return Text
       */
      virtual Text system_removeReservedPeer(Text peerId) = 0;

      /**
       * @brief Returns the list of reserved peers
       * @return Vec<Text>
       */
      virtual Vec<Text> system_reservedPeers() = 0;

      /**
       * @brief Resets the log filter to Substrate defaults
       * @warning This method is marked as unsafe.
       * @return Null
       */
      virtual Null system_resetLogFilter() = 0;

      /**
       * @brief Returns the state of the syncing of the node
       * @return SyncState
       */
      virtual SyncState system_syncState() = 0;

      /**
       * @brief Retrieves the version of the node
       * @return Text
       */
      virtual Text system_version() = 0;
   };
}
