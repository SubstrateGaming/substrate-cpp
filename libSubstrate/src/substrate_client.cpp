#include "logger.h"
#include "web/json_rpc_client.h"
#include "substrate_models.h"

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

   substrate::modules::RuntimeVersion getRuntimeVersion() const override
   {
      if (!_runtimeVersion.has_value())
      {
         throw std::runtime_error("Called client::getRuntimeVersion() without having the runtime version set.");
      }
      return _runtimeVersion.value();
   }

   void setRuntimeVersion(substrate::modules::RuntimeVersion version) override { _runtimeVersion = version; }

   substrate::models::Hash getGenesisHash() const override
   {
      if (!_genesisHash.has_value())
      {
         throw std::runtime_error("Called client::getGenesisHash() without having the hash set.");
      }
      return _genesisHash.value();
   }
   void setGenesisHash(substrate::models::Hash hash) override { _genesisHash = hash; }

   substrate::models::Extrinsic make_extrinsic(
      substrate::Account account,
      substrate::models::Method call,
      substrate::models::ChargeType charge = substrate::models::ChargeType(),
      uint32_t lifeTime = 0) const override
   {
      using namespace substrate::models;

      const auto genesisHash = getGenesisHash();
      const auto runtimeVersion = getRuntimeVersion();

      Hash checkpoint;
      substrate::models::Extrinsic extrinsic;

      extrinsic.Signed = true;
      extrinsic.TransactionVersion = substrate::constants::TransactionVersion;
      extrinsic.Account = account->get_account_id();

      if (lifeTime == 0)
      {
         extrinsic.Era = Era::make(0, 0);
         checkpoint = genesisHash;
      }
      else
      {
         checkpoint = getChainModule()->getFinalizedHead().value();
         const auto finalizedHeader = getChainModule()->getHeader(checkpoint).value();
         extrinsic.Era = Era::make(lifeTime, finalizedHeader.Number);
      }

      extrinsic.Nonce = getSystemModule()->getAccountNextIndex(account->get_address()).value();

      extrinsic.Charge = charge;
      extrinsic.Method = call;

      substrate::encoder encoder;
      encoder << substrate::models::detail::make_payload(extrinsic, genesisHash, checkpoint, runtimeVersion);

      extrinsic.Signature.Bytes = account->sign(encoder.assemble());
      extrinsic.Signature.Type = account->get_type();
      return extrinsic;
   }

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