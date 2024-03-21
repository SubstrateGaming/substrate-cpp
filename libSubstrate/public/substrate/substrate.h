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

   class ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class IClient;
   using Client = std::shared_ptr<IClient>;

   [[nodiscard]]
   LIB_SUBSTRATE_EXPORT std::string get_curl_version_info();

   class LIB_SUBSTRATE_EXPORT IClient
   {
   public:
      virtual ~IClient() = default;

      virtual bool connect() = 0;
      virtual bool connected() = 0;
      virtual void wait() = 0;
      virtual void chain_getBlockHash() = 0;
   };

   class LIB_SUBSTRATE_EXPORT ILogger
   {
   public:
      virtual ~ILogger() = default;

      virtual void debug(const std::string& category, const std::string& message) = 0;
      virtual void info(const std::string& category, const std::string& message) = 0;
      virtual void warn(const std::string& category, const std::string& message) = 0;
      virtual void error(const std::string& category, const std::string& message) = 0;
   };

   [[nodiscard]]
   LIB_SUBSTRATE_EXPORT Client make_client(Logger logger, const std::string& url);
}
