#pragma once
#include "../logger.h"
#include "../web/json_rpc_client.h"
#include "../substrate_models.h"

namespace substrate::detail::rpc
{
   using namespace substrate::rpc;
   using namespace substrate::detail::web;

   // TODO: Remove this completely
   using namespace substrate::models;

   class substrate_client final : public substrate::IClient
   {
      substrate::Logger _logger;

      std::string _url;
      json_rpc_client_ptr _socket;

      std::optional<substrate::modules::RuntimeVersion> _runtimeVersion;
      std::optional<Hash> _genesisHash;
      substrate::modules::Author _module_author;
      substrate::modules::Chain _module_chain;
      substrate::modules::Payment _module_payment;
      substrate::modules::State _module_state;
      substrate::modules::System _module_system;
      substrate::modules::UnstableCalls _module_unstable_calls;

      constexpr static auto kCategory = "substrate_client";

   public:
      substrate_client(substrate::Logger logger, const std::string &url);
      virtual ~substrate_client() = default;

      [[nodiscard]] virtual bool connect() override;
      [[nodiscard]] virtual bool connected() const override;

      virtual void wait() override;

      [[nodiscard]] virtual substrate::modules::RuntimeVersion getRuntimeVersion() const override;
      virtual void setRuntimeVersion(substrate::modules::RuntimeVersion version) override;

      [[nodiscard]] virtual Hash getGenesisHash() const override;
      virtual void setGenesisHash(Hash hash) override;

      [[nodiscard]] Extrinsic make_extrinsic(
         substrate::Account account,
         Method call,
         ChargeType charge = ChargeType(),
         uint32_t lifeTime = 0) const override;

      SUBSTRATE_IMPL_RPC_CLIENT

      [[nodiscard]] substrate::modules::Author getAuthorModule() const override { return _module_author; }
      [[nodiscard]] substrate::modules::Chain getChainModule() const override { return _module_chain; }
      [[nodiscard]] substrate::modules::Payment getPaymentModule() const override { return _module_payment; }
      [[nodiscard]] substrate::modules::State getStateModule() const override { return _module_state; }
      [[nodiscard]] substrate::modules::System getSystemModule() const override { return _module_system; }
      [[nodiscard]] substrate::modules::UnstableCalls getUnstableCallsModule() const override { return _module_unstable_calls; }
   };
}