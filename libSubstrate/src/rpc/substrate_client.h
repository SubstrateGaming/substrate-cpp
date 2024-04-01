#pragma once
#include "../logger.h"
#include "../web/json_rpc_client.h"
#include "../substrate_models.h"

namespace substrate::detail::rpc
{
   using namespace substrate::rpc;
   using namespace substrate::detail::web;

   class substrate_client final : public substrate::IClient
   {
      substrate::Logger _logger;

      std::string _url;
      json_rpc_client_ptr _socket;

      std::optional<substrate::modules::RuntimeVersion> _runtimeVersion;
      std::optional<substrate::models::Hash> _genesisHash;
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

      virtual bool connect() override;
      virtual bool connected() const override;
      virtual void wait() override;
      virtual substrate::modules::RuntimeVersion getRuntimeVersion() const override;
      virtual void setRuntimeVersion(substrate::modules::RuntimeVersion version) override;
      virtual substrate::models::Hash getGenesisHash() const override;
      virtual void setGenesisHash(substrate::models::Hash hash) override;

      substrate::models::Extrinsic make_extrinsic(
         substrate::Account account,
         substrate::models::Method call,
         substrate::models::ChargeType charge = substrate::models::ChargeType(),
         uint32_t lifeTime = 0) const;

      SUBSTRATE_IMPL_RPC_CLIENT

      substrate::modules::Author getAuthorModule() const override { return _module_author; }
      substrate::modules::Chain getChainModule() const override { return _module_chain; }
      substrate::modules::Payment getPaymentModule() const override { return _module_payment; }
      substrate::modules::State getStateModule() const override { return _module_state; }
      substrate::modules::System getSystemModule() const override { return _module_system; }
      substrate::modules::UnstableCalls getUnstableCallsModule() const override { return _module_unstable_calls; }
   };
}