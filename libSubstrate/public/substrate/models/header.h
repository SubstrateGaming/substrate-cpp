#pragma once
#include "digest.h"
#include "hash.h"

namespace substrate::models
{
   struct Header
   {
      Digest Digest;
      Hash ExtrinsicsRoot;
      uint64_t Number{0};
      Hash ParentHash;
      Hash StateRoot;
   };
}
