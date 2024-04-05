#include "websocket_client.h"

#include "logger.h"

#include <format>
#include <sstream>
#include <assert.h>

using namespace substrate::detail::web;

websocket_client::websocket_client(substrate::Logger logger, const std::string &url)
    : _logger(logger), _curl(curl_easy_init())
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
         SLOG_ERROR(kCategory, std::format("curl_easy_perform failed: {}", curl_easy_strerror(res)));

         curl_easy_cleanup(_curl);
         _curl = nullptr;
      }
   }
}

websocket_client::~websocket_client()
{
   stop();

   if (_curl)
   {
      curl_easy_cleanup(_curl);
      _curl = nullptr;
   }
}

bool websocket_client::connected() const
{
   return _curl != nullptr && !_shouldStop.load();
}

void websocket_client::start()
{
   _workerThread = std::thread(&websocket_client::on_receive, this);
}

void websocket_client::stop()
{
   _shouldStop.store(true);
   _cv.notify_one();
   if (_workerThread.joinable())
      _workerThread.join();
}

void websocket_client::wait()
{
   std::unique_lock<std::mutex> lock(_mtx);
   _cv.wait(lock);
}

bool websocket_client::send_message(const std::string &message)
{
   size_t sent = 0;
   CURLcode res = curl_ws_send(_curl, message.data(), message.size(), &sent, 0, CURLWS_TEXT);
   if (res != CURLE_OK)
   {
      SLOG_ERROR(kCategory, std::format("curl_easy_perform failed: {}", curl_easy_strerror(res)));
      return false;
   }
   assert(sent == message.size());
   return res == CURLE_OK && sent == message.size();
}

void websocket_client::on_receive()
{
   std::stringstream stream;
   char buffer[256] = {0};
   CURLcode res = CURLE_OK;
   size_t rlen = 0;
   std::unique_lock<std::mutex> lock(_mtx);

   while (!_shouldStop.load())
   {
      if (_shouldStop.load())
      {
         // Expected exit. All good.
         return;
      }

      const struct curl_ws_frame *meta;
      res = curl_ws_recv(_curl, buffer, sizeof(buffer), &rlen, &meta);

      if (res == CURLE_AGAIN)
      {
         // There is no curl_ws_poll API (yet).
         // We (could) extract the socket and select() on that but for now we simply wait a short time.
         _cv.wait_for(lock, std::chrono::milliseconds(100), [this] { return _shouldStop.load(); });
         continue;
      }

      if (res != CURLE_OK)
      {
         // Rather unexpected. Escalate.
         SLOG_ERROR(kCategory, std::format("curl_ws_recv failed: {}", curl_easy_strerror(res)));
         break;
      }

      assert((meta->flags & CURLWS_BINARY) == false);
      if ((meta->flags & CURLWS_TEXT) && rlen > 0)
         stream << std::string(&buffer[0], rlen);

      if ((meta->flags & CURLWS_CONT))
      {
         SLOG_DEBUG(kCategory, "curl_ws_recv received CURWS_CONT");
      }

      if ((meta->flags & CURLWS_CLOSE))
      {
         // Rather unexpected. Escalate.
         SLOG_DEBUG(kCategory, "curl_ws_recv received CURLWS_CLOSE");
         break;
      }

      if (meta->bytesleft == 0)
      {
         on_message(stream.str());
         stream = std::stringstream();
      }
   }

   // Rather unexpected. Escalate.
   _shouldStop.store(true);
   _cv.notify_all();
}

void websocket_client::on_message(const std::string& message)
{
   (void)message;
}
