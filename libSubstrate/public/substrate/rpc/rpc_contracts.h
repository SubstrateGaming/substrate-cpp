#pragma once

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT contracts
   {
   public:
      virtual ~contracts() = default;

      /**
       * @brief Executes a call to a contract
       * @deprecated This method is deprecated.
       * @param callRequest ContractCallRequest
       * @param at BlockHash
       * @return ContractExecResult
       */
      virtual ContractExecResult contracts_call(ContractCallRequest callRequest, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns the value under a specified storage key in a contract
       * @deprecated This method is deprecated.
       * @param address AccountId
       * @param key H256
       * @param at BlockHash
       * @return Option<Bytes>
       */
      virtual Option<Bytes> contracts_getStorage(AccountId address, H256 key, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Instantiate a new contract
       * @deprecated This method is deprecated.
       * @param request InstantiateRequestV1
       * @param at BlockHash
       * @return ContractInstantiateResult
       */
      virtual ContractInstantiateResult contracts_instantiate(InstantiateRequestV1 request, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Returns the projected time a given contract will be able to sustain paying its rent
       * @deprecated This method is deprecated.
       * @param address AccountId
       * @param at BlockHash
       * @return Option<BlockNumber>
       */
      virtual Option<BlockNumber> contracts_rentProjection(AccountId address, std::optional<BlockHash> at = std::nullopt) const = 0;

      /**
       * @brief Upload new code without instantiating a contract from it
       * @deprecated This method is deprecated.
       * @param uploadRequest CodeUploadRequest
       * @param at BlockHash
       * @return CodeUploadResult
       */
      virtual CodeUploadResult contracts_upload_code(CodeUploadRequest uploadRequest, std::optional<BlockHash> at = std::nullopt) const = 0;
   };
}

#ifndef SUBSTRATE_IMPL_RPC_CONTRACTS
#define SUBSTRATE_IMPL_RPC_CONTRACTS \
   virtual ContractExecResult contracts_call(ContractCallRequest callRequest, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Option<Bytes> contracts_getStorage(AccountId address, H256 key, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual ContractInstantiateResult contracts_instantiate(InstantiateRequestV1 request, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual Option<BlockNumber> contracts_rentProjection(AccountId address, std::optional<BlockHash> at = std::nullopt) const override; \
   virtual CodeUploadResult contracts_upload_code(CodeUploadRequest uploadRequest, std::optional<BlockHash> at = std::nullopt) const override;
#endif
