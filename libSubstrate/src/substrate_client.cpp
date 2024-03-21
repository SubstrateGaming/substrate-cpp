#include <curl/curl.h>

#include <assert.h>

#include "detail/logger.h"
#include "detail/json_rpc_client.h"

namespace detail = substrate::detail;

//
// client implementation
class client : public substrate::IClient
{
   substrate::Logger _logger;
   std::string _url;
   std::unique_ptr<detail::json_rpc_client> _socket;

   constexpr static auto kCategory = "client";

public:
   client(substrate::Logger logger, const std::string &url)
       : _logger(logger), _url(url)
   {
   }

   virtual ~client() override
   {
      _socket = nullptr;
   }

   bool connect() override
   {
      assert(_socket == nullptr);

      SLOG_DEBUG(kCategory, std::format("connecting to endpoint {}", _url));

      // build the rpc client and connect right away
      _socket = std::make_unique<detail::json_rpc_client>(_logger, _url);
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

   bool connected() override { return _socket && _socket->connected(); }

   void wait() override
   {
      assert(_socket != nullptr);
      if (_socket)
      {
         SLOG_DEBUG(kCategory, "wait until connection is closed");
         _socket->wait();
      }
   }

   void chain_getBlockHash()
   {
      assert(_socket);

      auto optResponse = _socket->send("chain_getBlockHash", std::vector<uint32_t>({0}));
      if (!optResponse.has_value())
      {
         _socket = nullptr;
      }

      auto value = optResponse.value();
   }
};

substrate::Client substrate::make_client(substrate::Logger logger, const std::string &url)
{
   return std::make_shared<client>(logger, url);
}