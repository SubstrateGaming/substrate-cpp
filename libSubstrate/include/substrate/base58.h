#pragma once
#include "types.h"

namespace substrate
{
   LIB_SUBSTRATE_EXPORT [[nodiscard]] std::string base58_encode(substrate::bytes input);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes base58_decode(const std::string& input);
}
