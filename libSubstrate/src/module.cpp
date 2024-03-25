#include "module.h"

using namespace substrate::models;
using json = nlohmann::json;

substrate::detail::module::module(substrate::Logger logger, web::json_rpc_client_ptr socket)
    : _logger(logger), _socket(socket)
{
}

Header substrate::detail::parse_header(const json& json)
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

BlockData substrate::detail::parse_block_data(const json& json)
{
   const auto& jsonBlock = json["block"];
   // const auto& jsonJustification = json["justification"];
   // TODO: How to parse justification?

   BlockData blockData;
   blockData.Block.Header = parse_header(jsonBlock["header"]);
   blockData.Block.Extrinsics = parse_extrinsics(jsonBlock["extrinsics"]);
   return blockData;
}

std::vector<Extrinsic> substrate::detail::parse_extrinsics(const json& json)
{
   assert(json.is_array());

   std::vector<Extrinsic> result;
   for (const auto& jsonExtrinsic : json)
   {
      substrate::decoder decoder(substrate::hex_decode(jsonExtrinsic));

      Extrinsic extrinsic;
      decoder >> extrinsic;
      result.emplace_back(extrinsic);
   }
   return result;
}
