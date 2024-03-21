#pragma once
#include <substrate/substrate.h>


namespace substrate::detail
{
   namespace web { class json_rpc_client; }

   class client final : public substrate::IClient
   {
      substrate::Logger _logger;
      std::string _url;
      std::unique_ptr<detail::web::json_rpc_client> _socket;

      constexpr static auto kCategory = "client";

   public:
      client(substrate::Logger logger, const std::string &url);
      virtual ~client() override;

      bool connect() override;
      bool connected() const override;
      void wait() override;

      substrate::modules::Author getAuthorModule() const override;
      substrate::modules::Chain getChainModule() const override;
      substrate::modules::Payment getPaymentModule() const override;
      substrate::modules::State getStateModule() const override;
      substrate::modules::System getSystemModule() const override;
      substrate::modules::UnstableCalls getUnstableCallsModule() const override;
   };
}
