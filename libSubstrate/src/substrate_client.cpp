#include "logger.h"
#include "web/json_rpc_client.h"

#include <assert.h>

using namespace substrate::detail::web;

// Forward private implementation
namespace substrate::detail::modules
{
   substrate::modules::Author make_module_author(substrate::Logger logger, json_rpc_client_ptr socket);
   substrate::modules::Chain make_module_chain(substrate::Logger logger, json_rpc_client_ptr socket);
   substrate::modules::Payment make_module_payment(substrate::Logger logger, json_rpc_client_ptr socket);
   substrate::modules::State make_module_state(substrate::Logger logger, json_rpc_client_ptr socket);
   substrate::modules::System make_module_system(substrate::Logger logger, json_rpc_client_ptr socket);
   substrate::modules::UnstableCalls make_module_unstable_calls(substrate::Logger logger, json_rpc_client_ptr socket);
}

using namespace substrate::detail::modules;

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
   substrate_client(substrate::Logger logger, const std::string &url)
       : _logger(logger), _url(url)
   {
   }

   bool connect()
   {
      assert(_socket == nullptr);

      SLOG_DEBUG(kCategory, std::format("connecting to endpoint {}", _url));

      // build the rpc client and connect right away
      _socket = std::make_shared<json_rpc_client>(_logger, _url);
      if (!_socket->connected())
      {
         // most likely a user error
         SLOG_DEBUG(kCategory, std::format("could not connect to endpoint {}", _url));

         _socket = nullptr;
         return false;
      }

      // initialize module interfaces
      _module_author = make_module_author(_logger, _socket);
      _module_chain = make_module_chain(_logger, _socket);
      _module_payment = make_module_payment(_logger, _socket);
      _module_state = make_module_state(_logger, _socket);
      _module_system = make_module_system(_logger, _socket);
      _module_unstable_calls = make_module_unstable_calls(_logger, _socket);

      // start receiving messages
      SLOG_DEBUG(kCategory, std::format("connected to endpoint {}, start receiving messages", _url));
      _socket->start();
      return true;
   }

   bool connected() const
   {
      return _socket && _socket->connected();
   }

   void wait()
   {
      assert(_socket != nullptr);
      if (_socket)
      {
         SLOG_DEBUG(kCategory, "wait until connection is closed");
         _socket->wait();
      }
   }

   std::optional<substrate::modules::RuntimeVersion> getRuntimeVersion() const override { return _runtimeVersion; }
   void setRuntimeVersion(substrate::modules::RuntimeVersion version) override { _runtimeVersion = version; }

   std::optional<substrate::models::Hash> getGenesisHash() const override { return _genesisHash; }
   void setGenesisHash(substrate::models::Hash hash) override { _genesisHash = hash; }

   substrate::modules::Author getAuthorModule() const override { return _module_author; }
   substrate::modules::Chain getChainModule() const override { return _module_chain; }
   substrate::modules::Payment getPaymentModule() const override { return _module_payment; }
   substrate::modules::State getStateModule() const override { return _module_state; }
   substrate::modules::System getSystemModule() const override { return _module_system; }
   substrate::modules::UnstableCalls getUnstableCallsModule() const override { return _module_unstable_calls; }
};

namespace substrate
{
   substrate::Client substrate::make_client(substrate::Logger logger, const std::string &url)
   {
      return std::make_shared<substrate_client>(logger, url);
   }
}