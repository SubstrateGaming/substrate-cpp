#pragma once
#include "types.h"

#include "logger.h"
#include "hex.h"
#include "decoder.h"
#include "encoder.h"

#include "modules/author.h"
#include "modules/chain.h"
#include "modules/payment.h"
#include "modules/state.h"
#include "modules/system.h"
#include "modules/unstable_calls.h"

#include "client.h"

namespace substrate
{
   namespace deps
   {
      [[nodiscard]] LIB_SUBSTRATE_EXPORT std::string get_curl_version_info();
   }
}
