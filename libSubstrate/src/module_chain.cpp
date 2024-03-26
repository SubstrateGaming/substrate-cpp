#include "module.h"

using namespace substrate::models;
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

   BlockData getBlock(std::optional<Hash> hash = std::nullopt) const override
   {
      auto params = json::array();
      if (hash.has_value())
         params.push_back(hash.value());

      const auto json = _socket->send_rpc_result("chain_getBlock", params);
      const auto result = parse_block_data(json);
      return result;
   }

   Hash getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const override
   {
      auto params = json::array();
      if (blockNumber.has_value())
      {
         substrate::encoder encoder;
         encoder << blockNumber.value();
         params.push_back(encoder.assemble_hex());
      }

      const auto result = _socket->send("chain_getBlockHash", params);
      return Hash{ result };
   }

   Hash getFinalizedHead() const override
   {
      const auto result = _socket->send("chain_getFinalizedHead");
      return Hash{ result };
   }

   Header getHeader(std::optional<Hash> hash = std::nullopt) const override
   {
      auto params = json::array();
      if (hash.has_value())
         params.push_back(hash.value());

      const auto json = _socket->send_rpc_result("chain_getHeader", params);
      const auto result = parse_header(json);
      return result;
   }
};

namespace substrate::detail::modules
{
   substrate::modules::Chain make_module_chain(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_chain>(logger, socket);
   }
}
