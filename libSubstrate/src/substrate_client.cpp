#include <substrate/substrate.h>
#include <curl/curl.h>

#include <assert.h>

#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <iostream>
#include <condition_variable>

class websocket_client
{
   CURL *_curl;
   std::thread _workerThread;
   std::atomic<bool> _shouldStop;
   std::mutex _mtx;
   std::condition_variable _cv;

public:
   websocket_client(const std::string &url)
       : _curl(curl_easy_init())
   {
      assert(_curl);
      assert(!url.empty());

      if (_curl)
      {
         curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());

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
   }

   bool connected() const { return _curl != nullptr && !_shouldStop.load(); }

   ~websocket_client()
   {
      stop();

      if (_curl)
      {
         curl_easy_cleanup(_curl);
         _curl = nullptr;
      }
   }

   bool send(const std::string &message)
   {
      size_t sent = 0;
      CURLcode res = curl_ws_send(_curl, message.data(), message.size(), &sent, 0, CURLWS_TEXT);
      if (res != CURLE_OK)
      {
         std::cerr << "curl_ws_send() failed: " << curl_easy_strerror(res) << std::endl;
         return false;
      }
      assert(sent == message.size());
      return res == CURLE_OK && sent == message.size();
   }

   void start() { _workerThread = std::thread(&websocket_client::receive, this); }

   void stop()
   {
      _shouldStop.store(true);
      _cv.notify_one();
      if (_workerThread.joinable())
         _workerThread.join();
   }

   void wait()
   {
      std::unique_lock<std::mutex> lock(_mtx);
      _cv.wait(lock);
   }

   void receive()
   {
      std::stringstream stream;
      char buffer[256] = {0};
      CURLcode res = CURLE_OK;
      size_t rlen = 0;
      std::unique_lock<std::mutex> lock(_mtx);

      while (!_shouldStop.load())
      {
         // There is no curl_ws_poll API (yet).
         // We (could) extract the socket and select() on that but for now we simply wait a short time.
         _cv.wait_for(lock, std::chrono::milliseconds(100), [this]
                      { return _shouldStop.load(); });

         if (_shouldStop.load())
         {
            // Expected exit. All good.
            return;
         }

         const struct curl_ws_frame *meta;
         res = curl_ws_recv(_curl, buffer, sizeof(buffer), &rlen, &meta);

         if (res == CURLE_AGAIN)
            continue;

         if (res != CURLE_OK)
         {
            // Rather unexpected. Escalate.
            std::cerr << "curl_ws_recv() failed: " << curl_easy_strerror(res) << std::endl;
            break;
         }

         assert((meta->flags & CURLWS_BINARY) == false);
         if ((meta->flags & CURLWS_TEXT) && rlen > 0)
            stream << std::string(&buffer[0], rlen);

         if ((meta->flags & CURLWS_CONT))
         {
            std::cout << "curl_ws_recv() received CURLWS_CONT" << std::endl;
         }

         if ((meta->flags & CURLWS_CLOSE))
         {
            // Rather unexpected. Escalate.
            std::cout << "curl_ws_recv() received CURLWS_CLOSE" << std::endl;
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

      // Rather unexpected. Escalate.
      _shouldStop.store(true);
      _cv.notify_all();
   }
};

//
// client implementation
class client : public substrate::IClient
{
   std::string _url;
   std::unique_ptr<websocket_client> _socket;

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
      _socket = std::make_unique<websocket_client>(_url);
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

   void send(const std::string &message)
   {
      assert(_socket);

      if (!_socket->send(message))
      {
         _socket = nullptr;
      }
   }

   // void receive()
   // {
   //    std::stringstream stream;
   //    char buffer[256] = {0};
   //    CURLcode res = CURLE_OK;
   //    size_t rlen = 0;
   //    while (1)
   //    {
   //       const struct curl_ws_frame *meta;
   //       res = curl_ws_recv(_curl, buffer, sizeof(buffer), &rlen, &meta);

   //       if (res == CURLE_AGAIN)
   //       {
   //          // There is no curl_ws_poll API (yet).
   //          // We (could) extract the socket and select() on that but for now we simply wait a short time.
   //          std::this_thread::sleep_for(std::chrono::milliseconds(100));
   //          continue;
   //       }

   //       if (res != CURLE_OK)
   //       {
   //          std::cerr << "curl_ws_recv() failed: " << curl_easy_strerror(res) << std::endl;
   //          curl_easy_cleanup(_curl);
   //          _curl = nullptr;
   //          break;
   //       }

   //       if ((meta->flags & CURLWS_TEXT))
   //       {
   //          std::cout << "curl_ws_recv() received CURLWS_TEXT" << std::endl;
   //          assert(rlen > 0);
   //          if (rlen == 0)
   //          {
   //             curl_easy_cleanup(_curl);
   //             _curl = nullptr;
   //             break;
   //          }

   //          stream << std::string(&buffer[0], rlen);
   //       }
   //       else if ((meta->flags & CURLWS_BINARY))
   //       {
   //          // We do not yet expect that.
   //          assert(false);
   //       }

   //       if ((meta->flags & CURLWS_CONT))
   //       {
   //          std::cout << "curl_ws_recv() received CURLWS_CONT" << std::endl;
   //       }

   //       if ((meta->flags & CURLWS_PING))
   //       {
   //          std::cout << "curl_ws_recv() received CURLWS_PING" << std::endl;
   //       }

   //       if ((meta->flags & CURLWS_CLOSE))
   //       {
   //          std::cout << "curl_ws_recv() received CURLWS_CLOSE" << std::endl;
   //          curl_easy_cleanup(_curl);
   //          _curl = nullptr;
   //          break;
   //       }

   //       if (meta->bytesleft == 0)
   //       {
   //          std::cout << "curl_ws_recv() completed message " << std::endl
   //                    << stream.str()
   //                    << std::endl;

   //          stream = std::stringstream();
   //       }
   //    }
   // }
};

substrate::Client substrate::make_client(const std::string &url)
{
   return std::make_shared<client>(url);
}