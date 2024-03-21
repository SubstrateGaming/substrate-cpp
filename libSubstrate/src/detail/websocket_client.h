#pragma once

#include <mutex>
#include <thread>
#include <string>
#include <unordered_map>
#include <condition_variable>

#include <curl/curl.h>

namespace substrate::detail
{
   class websocket_client
   {
      CURL *_curl;
      std::thread _workerThread;
      std::atomic<bool> _shouldStop;
      std::mutex _mtx;
      std::condition_variable _cv;

   public:
      websocket_client(const std::string &url);
      virtual ~websocket_client();

      bool connected() const;
      bool send(const std::string &message);
      void start();
      void stop();
      void wait();

   private:
      void on_receive();

   protected:
      virtual void on_message(std::string message);
   };
}