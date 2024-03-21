#pragma once
#include "substrate_export.h"

#include <memory>
#include <string>

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT ILogger;
   using Logger = std::shared_ptr<ILogger>;

   class LIB_SUBSTRATE_EXPORT IClient;
   using Client = std::shared_ptr<IClient>;
}
