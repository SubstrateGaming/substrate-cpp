#pragma once
#include "types.h"

namespace substrate
{
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::string base58_encode(substrate::bytes input);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT substrate::bytes base58_decode(const std::string& input);
}
