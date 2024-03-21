#include "substrate_client.h"

#include "logger.h"
#include "web/json_rpc_client.h"

#include <curl/curl.h>
#include <assert.h>

using namespace substrate::detail;

client::client(substrate::Logger logger, const std::string &url)
    : _logger(logger), _url(url)
{
}

client::~client()
{
   _socket = nullptr;
}

bool client::connect()
{
   assert(_socket == nullptr);

   SLOG_DEBUG(kCategory, std::format("connecting to endpoint {}", _url));

   // build the rpc client and connect right away
   _socket = std::make_unique<detail::web::json_rpc_client>(_logger, _url);
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

bool client::connected() const
{
   return _socket && _socket->connected();
}

void client::wait()
{
   assert(_socket != nullptr);
   if (_socket)
   {
      SLOG_DEBUG(kCategory, "wait until connection is closed");
      _socket->wait();
   }
}

substrate::modules::Author client::getAuthorModule() const
{
   return nullptr;
}

substrate::modules::Chain client::getChainModule() const
{
   return nullptr;
}

substrate::modules::Payment client::getPaymentModule() const
{
   return nullptr;
}

substrate::modules::State client::getStateModule() const
{
   return nullptr;
}

substrate::modules::System client::getSystemModule() const
{
   return nullptr;
}

substrate::modules::UnstableCalls client::getUnstableCallsModule() const
{
   return nullptr;
}

substrate::Client substrate::make_client(substrate::Logger logger, const std::string &url)
{
   return std::make_shared<client>(logger, url);
}
