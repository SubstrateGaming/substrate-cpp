#pragma once

#include "substrate_export.h"

#include <memory>
#include <string>

namespace substrate
{
   LIB_SUBSTRATE_EXPORT void library_init();
   LIB_SUBSTRATE_EXPORT void library_cleanup();

   namespace deps
   {
      [[nodiscard]]
      LIB_SUBSTRATE_EXPORT std::string get_curl_version_info();
   }

   class IClient;
   using Client = std::shared_ptr<IClient>;

   [[nodiscard]]
   LIB_SUBSTRATE_EXPORT std::string get_curl_version_info();


   [[nodiscard]]
   LIB_SUBSTRATE_EXPORT Client make_client(const std::string& url);

   class LIB_SUBSTRATE_EXPORT IClient
   {
   public:
      virtual ~IClient() = default;

      virtual bool connect() = 0;
      virtual bool connected() = 0;
      virtual void wait() = 0;
      virtual void send(const std::string& message) = 0;
   };
}
