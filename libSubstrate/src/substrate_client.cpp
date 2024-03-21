#include <substrate/substrate.h>
#include <curl/curl.h>

#include <assert.h>

#include "detail/json_rpc_client.h"

namespace detail = substrate::detail;

//
// client implementation
class client : public substrate::IClient
{
   std::string _url;
   std::unique_ptr<detail::json_rpc_client> _socket;

public:
   client(const std::string &url)
       : _url(url)
   {
   }

   virtual ~client() override
   {
      _socket = nullptr;
   }

   bool connect() override
   {
      assert(_socket == nullptr);
      _socket = std::make_unique<detail::json_rpc_client>(_url);
      if (!_socket->connected())
      {
         _socket = nullptr;
         return false;
      }

      // Start listening
      _socket->start();
      return true;
   }

   bool connected() override { return _socket && _socket->connected(); }

   void wait() override
   {
      assert(_socket != nullptr);
      if (_socket)
      {
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

substrate::Client substrate::make_client(const std::string &url)
{
   return std::make_shared<client>(url);
}