#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

ContractExecResult substrate_client::contracts_call(ContractCallRequest callRequest, std::optional<BlockHash> at) const
{
   return rpc<ContractExecResult>("contracts_call", callRequest, at);
}

Option<Bytes> substrate_client::contracts_getStorage(AccountId address, H256 key, std::optional<BlockHash> at) const
{
   return rpc<Option<Bytes>>("contracts_getStorage", address, key, at);
}

ContractInstantiateResult substrate_client::contracts_instantiate(InstantiateRequestV1 request, std::optional<BlockHash> at) const
{
   return rpc<ContractInstantiateResult>("contracts_instantiate", request, at);
}

Option<BlockNumber> substrate_client::contracts_rentProjection(AccountId address, std::optional<BlockHash> at) const
{
   return rpc<Option<BlockNumber>>("contracts_rentProjection", address, at);
}

CodeUploadResult substrate_client::contracts_upload_code(CodeUploadRequest uploadRequest, std::optional<BlockHash> at) const
{
   return rpc<CodeUploadResult>("contracts_upload_code", uploadRequest, at);
}

