#pragma once
#include "types.h"
#include "logger.h"
#include "rpc_client.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT IClient : public substrate::rpc::rpc_client
   {
   public:
      virtual ~IClient() = default;

      [[nodiscard]] virtual bool connect() = 0;
      [[nodiscard]] virtual bool connected() const = 0;

      virtual void wait() = 0;

      [[nodiscard]] virtual modules::RuntimeVersion getRuntimeVersion() const = 0;
      virtual void setRuntimeVersion(modules::RuntimeVersion version) = 0;

      [[nodiscard]] virtual models::Hash getGenesisHash() const = 0;
      virtual void setGenesisHash(models::Hash hash) = 0;

      [[nodiscard]] virtual substrate::models::Extrinsic make_extrinsic(substrate::Account account, substrate::models::Method call, substrate::models::ChargeType charge = substrate::models::ChargeType(), uint32_t lifeTime = 0) const = 0;

      [[nodiscard]] virtual modules::Author getAuthorModule() const = 0;
      [[nodiscard]] virtual modules::Chain getChainModule() const = 0;
      [[nodiscard]] virtual modules::Payment getPaymentModule() const = 0;
      [[nodiscard]] virtual modules::State getStateModule() const = 0;
      [[nodiscard]] virtual modules::System getSystemModule() const = 0;
      [[nodiscard]] virtual modules::UnstableCalls getUnstableCallsModule() const = 0;
   };

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Client make_client(Logger logger, const std::string &url);
}
