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
      virtual ContractExecResult contracts_call(ContractCallRequest callRequest, BlockHash at = {}) = 0;

      /**
       * @brief Returns the value under a specified storage key in a contract
       * @deprecated This method is deprecated.
       * @param address AccountId
       * @param key H256
       * @param at BlockHash
       * @return Option<Bytes>
       */
      virtual Option<Bytes> contracts_getStorage(AccountId address, H256 key, BlockHash at = {}) = 0;

      /**
       * @brief Instantiate a new contract
       * @deprecated This method is deprecated.
       * @param request InstantiateRequestV1
       * @param at BlockHash
       * @return ContractInstantiateResult
       */
      virtual ContractInstantiateResult contracts_instantiate(InstantiateRequestV1 request, BlockHash at = {}) = 0;

      /**
       * @brief Returns the projected time a given contract will be able to sustain paying its rent
       * @deprecated This method is deprecated.
       * @param address AccountId
       * @param at BlockHash
       * @return Option<BlockNumber>
       */
      virtual Option<BlockNumber> contracts_rentProjection(AccountId address, BlockHash at = {}) = 0;

      /**
       * @brief Upload new code without instantiating a contract from it
       * @deprecated This method is deprecated.
       * @param uploadRequest CodeUploadRequest
       * @param at BlockHash
       * @return CodeUploadResult
       */
      virtual CodeUploadResult contracts_upload_code(CodeUploadRequest uploadRequest, BlockHash at = {}) = 0;
   };
}
