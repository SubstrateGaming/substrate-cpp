#pragma once
#include "types.h"

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace substrate
{
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::string hex_encode(const std::vector<uint8_t>& input);
   [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<uint8_t> hex_decode(std::string input);
}
