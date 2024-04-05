#include "substrate_client.h"

#include <assert.h>

using namespace substrate::rpc;
using namespace substrate::rpc::detail;

using namespace substrate::detail::web;

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

   // start receiving messages
   SLOG_DEBUG(kCategory, std::format("connected to endpoint {}, start receiving messages", _url));
   _socket->start();
   return true;
}

bool substrate_client::connected() const
{
   return _socket && _socket->connected();
}

void substrate_client::stop()
{
   if (_socket)
   {
      _socket->stop();
   }
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

RuntimeVersion substrate_client::getRuntimeVersion() const
{
   if (!_runtimeVersion.has_value())
   {
      throw std::runtime_error("Called client::getRuntimeVersion() without having the runtime version set.");
   }
   return _runtimeVersion.value();
}

void substrate_client::setRuntimeVersion(RuntimeVersion version)
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
      checkpoint = chain_getFinalizedHead();
      const auto finalizedHeader = chain_getHeader(checkpoint);
      extrinsic.Era = Era::make(lifeTime, finalizedHeader.number);
   }

   extrinsic.Nonce = system_accountNextIndex(account->get_account_id());

   extrinsic.Charge = charge;
   extrinsic.Method = call;

   substrate::encoder encoder;
   encoder << substrate::rpc::Payload::make(extrinsic, genesisHash, checkpoint, runtimeVersion);

   extrinsic.Signature.Bytes = account->sign(encoder.assemble());
   extrinsic.Signature.Type = account->get_type();
   return extrinsic;
}

namespace substrate
{
   substrate::rpc::Client substrate::rpc::make_client(substrate::Logger logger, const std::string &url)
   {
      return std::make_shared<substrate_client>(logger, url);
   }
}
