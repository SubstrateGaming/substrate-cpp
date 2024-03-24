#include "module.h"

using namespace substrate::models;
using namespace substrate::detail;
using namespace substrate::detail::web;

using json = nlohmann::json;

Header parse_header(const json& json)
{
   assert(json.is_object());

   Header header;
   header.ExtrinsicsRoot = Hash{json["extrinsicsRoot"]};
   header.ParentHash = Hash{json["parentHash"]};
   header.StateRoot = Hash{json["stateRoot"]};
   header.Number = std::stoull(static_cast<std::string>(json["number"]), nullptr, 16);

   auto jsonDigest = json["digest"];
   if (jsonDigest.contains("logs"))
   {
      auto jsonLogs = jsonDigest["logs"];
      for (const auto &jsonLogItem : jsonLogs)
         header.Digest.Logs.emplace_back(jsonLogItem);
   }

   return header;
}

std::vector<Extrinsic> parse_extrinsics(const json& json)
{
   assert(json.is_array());

   std::vector<Extrinsic> result;
   for (const auto& jsonExtrinsic : json)
   {
      substrate::decoder decoder(substrate::hex_decode(jsonExtrinsic));

      Extrinsic extrinsic;
      decoder >> extrinsic;

      // TODO: Decode
      result.emplace_back(extrinsic);
   }
   return result;
}

BlockData parse_block_data(const json& json)
{
   const auto& jsonBlock = json["block"];
   // const auto& jsonJustification = json["justification"];
   // TODO: How to parse justification?

   BlockData blockData;
   blockData.Block.Header = parse_header(jsonBlock["header"]);
   blockData.Block.Extrinsics = parse_extrinsics(jsonBlock["extrinsics"]);
   return blockData;
}

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
      auto params = json::array();
      if (hash.has_value())
      {
         params.push_back(hash.value());
      }

      auto response = _socket->send_rpc_result("chain_getBlock", params);
      if (response.has_value())
      {
         const auto& json = response.value();
         return parse_block_data(json);
      }

      return std::nullopt;
   }

   std::optional<Hash> getBlockHash(std::optional<BlockNumber> blockNumber = std::nullopt) const override
   {
      auto params = json::array();
      if (blockNumber.has_value())
      {
         substrate::encoder encoder;
         encoder << blockNumber.value();
         params.push_back(encoder.assemble_hex());
      }

      auto response = _socket->send("chain_getBlockHash", params);
      if (response.has_value())
         return Hash{response.value()};

      return std::nullopt;
   }

   std::optional<Hash> getFinalizedHead() const override
   {
      auto response = _socket->send("chain_getFinalizedHead");
      if (response.has_value())
         return Hash{response.value()};

      return std::nullopt;
   }

   std::optional<Header> getHeader(std::optional<Hash> hash = std::nullopt) const override
   {
      auto params = json::array();
      if (hash.has_value())
      {
         params.push_back(hash.value());
      }

      auto response = _socket->send_rpc_result("chain_getHeader", params);
      if (response.has_value())
      {
         const auto& json = response.value();
         return parse_header(json);
      }

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
