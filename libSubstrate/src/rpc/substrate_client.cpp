#include "substrate_client.h"

#include <assert.h>

using namespace substrate::detail::rpc;
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

substrate_client::substrate_client(substrate::Logger logger, const std::string &url)
    : _logger(logger), _url(url)
{
}

bool substrate_client::connect()
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

bool substrate_client::connected() const
{
   return _socket && _socket->connected();
}

void substrate_client::wait()
{
   assert(_socket != nullptr);
   if (_socket)
   {
      SLOG_DEBUG(kCategory, "wait until connection is closed");
      _socket->wait();
   }
}

substrate::modules::RuntimeVersion substrate_client::getRuntimeVersion() const
{
   if (!_runtimeVersion.has_value())
   {
      throw std::runtime_error("Called client::getRuntimeVersion() without having the runtime version set.");
   }
   return _runtimeVersion.value();
}

void substrate_client::setRuntimeVersion(substrate::modules::RuntimeVersion version)
{
   _runtimeVersion = version;
}

Hash substrate_client::getGenesisHash() const
{
   if (!_genesisHash.has_value())
   {
      throw std::runtime_error("Called client::getGenesisHash() without having the hash set.");
   }
   return _genesisHash.value();
}

void substrate_client::setGenesisHash(Hash hash)
{
   _genesisHash = hash;
}

Extrinsic substrate_client::make_extrinsic(
    substrate::Account account,
    Method call,
    ChargeType charge,
    uint32_t lifeTime) const
{
   using namespace substrate::models;

   const auto genesisHash = getGenesisHash();
   const auto runtimeVersion = getRuntimeVersion();

   Hash checkpoint;
   Extrinsic extrinsic;

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
      checkpoint = getChainModule()->getFinalizedHead();
      const auto finalizedHeader = getChainModule()->getHeader(checkpoint);
      extrinsic.Era = Era::make(lifeTime, finalizedHeader.Number);
   }

   extrinsic.Nonce = getSystemModule()->getAccountNextIndex(account->get_address());

   extrinsic.Charge = charge;
   extrinsic.Method = call;

   substrate::encoder encoder;
   encoder << substrate::models::detail::make_payload(extrinsic, genesisHash, checkpoint, runtimeVersion);

   extrinsic.Signature.Bytes = account->sign(encoder.assemble());
   extrinsic.Signature.Type = account->get_type();
   return extrinsic;
}

namespace substrate
{
   substrate::Client substrate::make_client(substrate::Logger logger, const std::string &url)
   {
      return std::make_shared<substrate_client>(logger, url);
   }
}
