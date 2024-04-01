#include <substrate/substrate.h>

#include <mutex>
#include <format>
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
      std::cout << "DBG"
                << ": [" << category << "]:" << message << std::endl;
   }
   virtual void info(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "INFO"
                << ": [" << category << "]:" << message << std::endl;
   }
   virtual void warn(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "WARN"
                << ": [" << category << "]:" << message << std::endl;
   }
   virtual void error(const std::string &category, const std::string &message) override
   {
      std::lock_guard<std::mutex> lock(_mutex);
      std::cout << "ERR"
                << ": [" << category << "]:" << message << std::endl;
   }
};

int main(int argc, char **argv)
{
   std::cout << "Hello, Substrate Client!" << std::endl;

   auto client = substrate::rpc::make_client(std::make_shared<logger>(), "ws://172.16.20.2:9944");
   if (!client->connect())
      return -1;

   std::cout << "Get metadata...";
   const auto runtimeVersion = client->state_getRuntimeVersion();
   client->setRuntimeVersion(runtimeVersion);

   std::cout << std::format("Runtime version is: {}, spec version is {}, transaction version is {}, node is {}",
      runtimeVersion.ImplVersion,
      runtimeVersion.SpecVersion,
      runtimeVersion.TransactionVersion,
      runtimeVersion.ImplName) << std::endl;

   const auto genesisHash = client->chain_getBlockHash(substrate::rpc::BlockNumber(0));
   client->setGenesisHash(genesisHash);
   std::cout << std::format("Genesis hash is {}", genesisHash.value()) << std::endl;

   std::cout << "Client is connected, waiting until exit!" << std::endl;

   auto account = substrate::development::make_account_alice();
   substrate::rpc::Method method;
   method.ModuleIndex = 6;
   method.CallIndex = 7;
   method.Parameters = substrate::hex_decode("0x008eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a480b00a014e33226");

   const auto extrinsic = client->make_extrinsic(account, method);
   auto id = client->author_submitExtrinsic(extrinsic);
   std::cout << "Extrinsic is " << id.value() << std::endl;

   // Debug
   // std::cout << "Extrinsic subscription id is " << id << std::endl;
   // client->getChainModule()->getBlockHash(1);
   // client->getChainModule()->getFinalizedHead();
   // auto header = client->getChainModule()->getHeader();
   // auto block = client->getChainModule()->getBlock();
   // auto pending = client->getAuthorModule()->getPendingExtrinsic();

   client->wait();

   std::cout << "Stopping" << std::endl;
   client = nullptr;

   return 0;
}