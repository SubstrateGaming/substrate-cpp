#pragma once
#include <substrate/substrate.h>

namespace substrate::detail
{
   namespace web
   {
      class json_rpc_client;
   }

   class client final : public substrate::IClient
   {
      substrate::Logger _logger;
      std::string _url;
      std::unique_ptr<detail::web::json_rpc_client> _socket;
      substrate::modules::Author _module_author;
      substrate::modules::Chain _module_chain;
      substrate::modules::Payment _module_payment;
      substrate::modules::State _module_state;
      substrate::modules::System _module_system;
      substrate::modules::UnstableCalls _module_unstable_calls;

      constexpr static auto kCategory = "client";

   public:
      client(substrate::Logger logger, const std::string &url);
      virtual ~client() override;

      bool connect() override;
      bool connected() const override;
      void wait() override;

      substrate::modules::Author getAuthorModule() const override { return _module_author; }
      substrate::modules::Chain getChainModule() const override { return _module_chain; }
      substrate::modules::Payment getPaymentModule() const override { return _module_payment; }
      substrate::modules::State getStateModule() const override { return _module_state; }
      substrate::modules::System getSystemModule() const override { return _module_system; }
      substrate::modules::UnstableCalls getUnstableCallsModule() const override { return _module_unstable_calls; }
   };
}
