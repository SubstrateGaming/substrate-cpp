#include "rpc_test.h"

class stub_logger : public substrate::ILogger
{
public:
   stub_logger() = default;
   virtual ~stub_logger() override = default;
   virtual void debug(const std::string &category, const std::string &message) override
   {
      (void)category;
      (void)message;
   }

   virtual void info(const std::string &category, const std::string &message) override
   {
      (void)category;
      (void)message;
   }

   virtual void warn(const std::string &category, const std::string &message) override
   {
      (void)category;
      (void)message;
   }

   virtual void error(const std::string &category, const std::string &message) override
   {
      (void)category;
      (void)message;
   }
};

void rpc_test::SetUp()
{
   client = substrate::rpc::make_client(std::make_shared<stub_logger>(), "ws://172.16.20.2:9944");
   if (!client->connect())
   {
      throw std::runtime_error("could not prepare test, cannot connect to node");
      client = nullptr;
   }

   client->setRuntimeVersion(client->state_getRuntimeVersion());
   client->setGenesisHash(client->chain_getBlockHash(substrate::rpc::BlockNumber(0)));
}

void rpc_test::TearDown()
{
   client = nullptr;
}
