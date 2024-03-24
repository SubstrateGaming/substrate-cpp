#pragma once
#include "types.h"

namespace substrate
{
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<uint8_t> blake2(const std::vector<uint8_t>& input, size_t size = 128, const std::vector<uint8_t>& key = {});
}
