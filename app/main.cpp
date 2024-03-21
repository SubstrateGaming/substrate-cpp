#include <substrate/substrate.h>

#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
   substrate::library_init();

   std::cout << "Hello, Substrate Client!" << std::endl;
   std::cout << substrate::deps::get_curl_version_info() << std::endl;

   auto client = substrate::make_client("ws://192.168.88.147:9944");
   client->connect();
   if (!client->connected())
      return -1;

   client->chain_getBlockHash();

   std::cout << "Client is connected, waiting until exit!" << std::endl;
   client->wait();

   std::cout << "Stopping" << std::endl;
   client = nullptr;

   substrate::library_cleanup();
   return 0;
}