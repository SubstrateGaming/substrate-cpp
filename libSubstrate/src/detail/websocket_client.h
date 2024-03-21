#pragma once

#include <mutex>
#include <thread>
#include <string>
#include <unordered_map>
#include <condition_variable>

#include <curl/curl.h>
#include <substrate/substrate.h>

namespace substrate::detail
{
   class websocket_client
   {
      constexpr static auto kCategory = "websocket_client";

      CURL *_curl;
      std::thread _workerThread;
      std::atomic<bool> _shouldStop;
      std::mutex _mtx;
      std::condition_variable _cv;

   protected:
      substrate::Logger _logger;

   public:
      websocket_client(substrate::Logger logger, const std::string &url);
      virtual ~websocket_client();

      bool connected() const;
      bool send(const std::string &message);
      void start();
      void stop();
      void wait();

   private:
      void on_receive();

   protected:
      virtual void on_message(const std::string& message);
   };
}