#include <substrate/substrate.h>

#include <mutex>
#include <thread>
#include <iostream>

class logger : public substrate::ILogger
{
   std::mutex _mutex;

public:
   logger() = default;
   virtual ~logger() override = default;
   virtual void debug(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "DBG "
                << ":" << category << ":" << message << std::endl;
   }
   virtual void info(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "INFO "
                << ":" << category << ":" << message << std::endl;
   }
   virtual void warn(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "WARN "
                << ":" << category << ":" << message << std::endl;
   }
   virtual void error(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "ERR "
                << ":" << category << ":" << message << std::endl;
   }
};

int main(int argc, char **argv)
{
   std::cout << "Hello, Substrate Client!" << std::endl;
   std::cout << substrate::deps::get_curl_version_info() << std::endl;

   auto client = substrate::make_client(std::make_shared<logger>(), "ws://192.168.88.147:9944");
   if (!client->connect())
      return -1;

   std::cout << "Client is connected, waiting until exit!" << std::endl;
   client->wait();

   std::cout << "Stopping" << std::endl;
   client = nullptr;

   return 0;
}