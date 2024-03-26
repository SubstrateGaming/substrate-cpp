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

   virtual void submitExtrinsic(const Extrinsic& extrinsic) const
   {
      substrate::encoder encoder;
      encoder << extrinsic;

      const auto params = json::array({ encoder.assemble_hex() });
      _socket->send_rpc_result("author_submitExtrinsic", params);
   }
};

namespace substrate::detail::modules
{
   substrate::modules::Author make_module_author(substrate::Logger logger, json_rpc_client_ptr socket)
   {
      return std::make_shared<module_author>(logger, socket);
   }
}
