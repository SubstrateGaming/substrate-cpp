#include "substrate_client.h"

#include "logger.h"
#include "web/json_rpc_client.h"

#include <curl/curl.h>
#include <assert.h>

using namespace substrate::detail;

// Forward private implementation
namespace substrate::detail::modules
{
   substrate::modules::Author make_module_author();
   substrate::modules::Chain make_module_chain();
   substrate::modules::Payment make_module_payment();
   substrate::modules::State make_module_state();
   substrate::modules::System make_module_system();
   substrate::modules::UnstableCalls make_module_unstable_calls();
}

// Client implementation
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

   // initialize module interfaces
   _module_author = modules::make_module_author();
   _module_chain = modules::make_module_chain();
   _module_payment = modules::make_module_payment();
   _module_state = modules::make_module_state();
   _module_system = modules::make_module_system();
   _module_unstable_calls = modules::make_module_unstable_calls();

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

substrate::Client substrate::make_client(substrate::Logger logger, const std::string &url)
{
   return std::make_shared<client>(logger, url);
}
