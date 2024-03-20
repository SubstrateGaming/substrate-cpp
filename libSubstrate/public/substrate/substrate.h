#pragma once

#include "substrate_export.h"

#include <string>

namespace substrate
{
   namespace deps
   {
      [[nodiscard]]
      LIB_SUBSTRATE_EXPORT std::string get_curl_version_info();
   }
}
