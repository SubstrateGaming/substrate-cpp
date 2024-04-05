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
   LIB_SUBSTRATE_EXPORT [[nodiscard]] std::string hex_encode(const substrate::bytes& input);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes hex_decode(std::string input);
}
