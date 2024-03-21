#include "module.h"

using namespace substrate;
using namespace substrate::detail;
using namespace substrate::detail::web;

using json = nlohmann::json;

class module_chain : public module, public substrate::modules::IChain
{
public:
   module_chain(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_chain() override = default;

   std::optional<BlockData> getBlock(std::optional<Hash> hash = std::nullopt) const override
   {
      return std::nullopt;
   }

   std::optional<Hash> getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const override
   {
      auto params = json::array();
      if (blockNumber.has_value())
         params.push_back("0x04"); // 1 in scale-codec

      auto response = _socket->send("chain_getBlockHash", params);
      if (response.has_value())
      {
      }
      return std::nullopt;
   }

   std::optional<Hash> getFinalizedHead() const override
   {
      return std::nullopt;
   }

   std::optional<Header> getHeader(std::optional<Hash> hash = std::nullopt) const override
   {
      return std::nullopt;
   }
};

namespace substrate::detail::modules
{
   substrate::modules::Chain make_module_chain(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_chain>(logger, socket);
   }
}
