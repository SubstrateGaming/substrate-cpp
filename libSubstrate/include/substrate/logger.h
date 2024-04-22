#pragma once
#include "substrate_export.h"

#include <string>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger
   {
   public:
      virtual ~ILogger() = default;
      virtual void debug(const std::string &category, const std::string &message) = 0;
      virtual void info(const std::string &category, const std::string &message) = 0;
      virtual void warn(const std::string &category, const std::string &message) = 0;
      virtual void error(const std::string &category, const std::string &message) = 0;
   };
}
