#pragma once
#include "types.h"
#include "logger.h"
#include "rpc_types.h"
#include "rpc_client.h"

namespace substrate::rpc
{
   class LIB_SUBSTRATE_EXPORT IClient : public rpc_client
   {
   public:
      virtual ~IClient() = default;

      [[nodiscard]] virtual bool connect() = 0;
      [[nodiscard]] virtual bool connected() const = 0;

      virtual void wait() = 0;

      [[nodiscard]] virtual RuntimeVersion getRuntimeVersion() const = 0;
      virtual void setRuntimeVersion(RuntimeVersion version) = 0;

      [[nodiscard]] virtual Hash getGenesisHash() const = 0;
      virtual void setGenesisHash(Hash hash) = 0;

      [[nodiscard]] virtual Extrinsic make_extrinsic(substrate::Account account, Method call, ChargeType charge = ChargeType(), uint32_t lifeTime = 0) const = 0;
   };

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Client make_client(Logger logger, const std::string &url);
}
