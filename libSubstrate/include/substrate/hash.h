#pragma once
#include "types.h"

namespace substrate::hash
{
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes sha256(const substrate::bytes& input);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes sha512(const substrate::bytes& input);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] substrate::bytes blake2(const substrate::bytes& input, size_t size = 128, const substrate::bytes& key = {});
}
