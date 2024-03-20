#include <substrate/substrate.h>

#include <iostream>

int main(int argc, char** argv)
{
   substrate::library_init();

   std::cout << "Hello, Substrate Client!" << std::endl;
   std::cout << substrate::deps::get_curl_version_info() << std::endl;

   auto client = substrate::make_client("ws://192.168.88.147:9944");
   client->connect();
   if (!client->connected())
      return -1;

   client->send("{\"id\":1,\"jsonrpc\":\"2.0\",\"method\":\"chain_getBlockHash\",\"params\":[0]}");

   client->receive();

   substrate::library_cleanup();
   return 0;
}