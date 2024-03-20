#include <substrate/substrate.h>
#include <curl/curl.h>

#include <assert.h>

#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>

//
// Callback function for receiving WebSocket messages
static size_t on_receive(void *data, size_t size, size_t nmemb, void *userp)
{
   size_t real_size = size * nmemb;
   std::string message(static_cast<char *>(data), real_size);
   std::cout << "Received message: " << message << std::endl;
   // Process the received message here
   return real_size;
}

//
// client implementation
class client : public substrate::IClient
{
   struct connection_info
   {
   };

   CURL *_curl{nullptr};
   std::string _node_url;

public:
   client(const std::string &url)
       : _node_url(url)
   {
   }

   virtual ~client() override
   {
      if (_curl)
      {
         curl_easy_cleanup(_curl);
         _curl = nullptr;
      }
   }

   void connect() override
   {
      assert(!_node_url.empty());
      assert(_curl == nullptr);

      _curl = curl_easy_init();
      if (_curl == nullptr)
         return;

      curl_easy_setopt(_curl, CURLOPT_URL, _node_url.c_str());

      // https://curl.se/libcurl/c/libcurl-ws.html
      // Use the "Connect_only model"
      curl_easy_setopt(_curl, CURLOPT_CONNECT_ONLY, 2L); /* websocket style */

      // Perform the WebSocket handshake
      CURLcode res = curl_easy_perform(_curl);
      if (res != CURLE_OK)
      {
         std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

         curl_easy_cleanup(_curl);
         _curl = nullptr;
      }
   }

   bool connected() override { return _curl != nullptr; }

   void send(const std::string& message)
   {
      assert(_curl != nullptr);

      size_t sent = 0;
      CURLcode res = curl_ws_send(_curl, message.data(), message.size(), &sent, 0, CURLWS_TEXT);
      assert(sent == message.size());

      if (res != CURLE_OK)
      {
         std::cerr << "curl_ws_send() failed: " << curl_easy_strerror(res) << std::endl;
         curl_easy_cleanup(_curl);
         _curl = nullptr;
      }
   }

   void receive()
   {
      std::stringstream stream;
      char buffer[256] = {0};
      CURLcode res = CURLE_OK;
      size_t rlen = 0;
      while (1)
      {
         const struct curl_ws_frame *meta;
         res = curl_ws_recv(_curl, buffer, sizeof(buffer), &rlen, &meta);

         if (res == CURLE_AGAIN)
         {
            // There is no curl_ws_poll API (yet).
            // We (could) extract the socket and select() on that but for now we simply wait a short time.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
         }

         if (res != CURLE_OK)
         {
            std::cerr << "curl_ws_recv() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(_curl);
            _curl = nullptr;
            break;
         }

         if ((meta->flags & CURLWS_TEXT))
         {
            std::cout << "curl_ws_recv() received CURLWS_TEXT" << std::endl;
            assert(rlen > 0);
            if (rlen == 0)
            {
               curl_easy_cleanup(_curl);
               _curl = nullptr;
               break;
            }

            stream << std::string(&buffer[0], rlen);
         }
         else if ((meta->flags & CURLWS_BINARY))
         {
            // We do not yet expect that.
            assert(false);
         }

         if ((meta->flags & CURLWS_CONT))
         {
            std::cout << "curl_ws_recv() received CURLWS_CONT" << std::endl;
         }

         if ((meta->flags & CURLWS_PING))
         {
            std::cout << "curl_ws_recv() received CURLWS_PING" << std::endl;
         }

         if ((meta->flags & CURLWS_CLOSE))
         {
            std::cout << "curl_ws_recv() received CURLWS_CLOSE" << std::endl;
            curl_easy_cleanup(_curl);
            _curl = nullptr;
            break;
         }

         if (meta->bytesleft == 0)
         {
            std::cout << "curl_ws_recv() completed message " << std::endl
                      << stream.str()
                      << std::endl;

            stream = std::stringstream();
         }
      }
   }
};

substrate::Client substrate::make_client(const std::string &url)
{
   return std::make_shared<client>(url);
}