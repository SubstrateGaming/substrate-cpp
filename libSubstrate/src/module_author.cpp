#include "module.h"

using namespace substrate::models;
using namespace substrate::detail;
using namespace substrate::detail::web;

class module_author : public module, public substrate::modules::IAuthor
{
public:
   module_author(substrate::Logger logger, json_rpc_client_ptr socket)
       : module(logger, socket)
   {
   }

   virtual ~module_author() override = default;

   virtual std::vector<Extrinsic> getPendingExtrinsic() const
   {
      const auto json = _socket->send_rpc_result("author_pendingExtrinsics");
      const auto result = parse_extrinsics(json);
      return result;
   }

   virtual Hash submitExtrinsic(const Extrinsic& extrinsic) const
   {
      substrate::encoder encoder;
      encoder << extrinsic;

      const auto params = json::array({ encoder.assemble_hex() });
      const auto json = _socket->send_rpc_result("author_submitExtrinsic", params);
      return Hash{json};
   }

   virtual std::string submitExtrinsicSubscribe(const Extrinsic& extrinsic)
   {
      substrate::encoder encoder;
      encoder << extrinsic;

      // TEST
      const auto params = json::array({ encoder.assemble_hex() });
      const auto json = _socket->send_rpc_result("author_submitAndWatchExtrinsic", params, [this](nlohmann::json result) {
         SLOG_INFO("callback", std::format("received response: {}", result.dump()));
      });
      return std::string{json};
   }
};

namespace substrate::detail::modules
{
   substrate::modules::Author make_module_author(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_author>(logger, socket);
   }
}
