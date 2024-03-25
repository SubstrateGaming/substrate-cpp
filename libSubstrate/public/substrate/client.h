#pragma once
#include "types.h"
#include "logger.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT IClient
   {
   public:
      virtual ~IClient() = default;

      [[nodiscard]] virtual bool connect() = 0;
      [[nodiscard]] virtual bool connected() const = 0;

      virtual void wait() = 0;

      [[nodiscard]] virtual std::optional<modules::RuntimeVersion> getRuntimeVersion() const = 0;
      virtual void setRuntimeVersion(modules::RuntimeVersion version) = 0;

      [[nodiscard]] virtual std::optional<models::Hash> getGenesisHash() const = 0;
      virtual void setGenesisHash(models::Hash hash) = 0;

      [[nodiscard]] virtual modules::Author getAuthorModule() const = 0;
      [[nodiscard]] virtual modules::Chain getChainModule() const = 0;
      [[nodiscard]] virtual modules::Payment getPaymentModule() const = 0;
      [[nodiscard]] virtual modules::State getStateModule() const = 0;
      [[nodiscard]] virtual modules::System getSystemModule() const = 0;
      [[nodiscard]] virtual modules::UnstableCalls getUnstableCallsModule() const = 0;
   };

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Client make_client(Logger logger, const std::string &url);
}
