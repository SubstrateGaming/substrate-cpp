#pragma once
#include "types.h"

namespace substrate
{
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::string base58_encode(std::vector<uint8_t> input);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<uint8_t> base58_decode(const std::string& input);
}
