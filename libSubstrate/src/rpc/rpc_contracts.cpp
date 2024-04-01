#include "substrate_client.h"

using namespace substrate::rpc;
using namespace substrate::detail::rpc;

ContractExecResult substrate_client::contracts_call(ContractCallRequest callRequest, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Option<Bytes> substrate_client::contracts_getStorage(AccountId address, H256 key, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

ContractInstantiateResult substrate_client::contracts_instantiate(InstantiateRequestV1 request, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

Option<BlockNumber> substrate_client::contracts_rentProjection(AccountId address, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

CodeUploadResult substrate_client::contracts_upload_code(CodeUploadRequest uploadRequest, std::optional<BlockHash> at)
{
   throw std::runtime_error("not implemented");
}

