#include <substrate/substrate.h>

#include <cmath>
#include <cstdint>
#include <algorithm>

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Method& v)
{
   encoder << v.ModuleIndex;
   encoder << v.CallIndex;
   encoder << v.Parameters;
   return encoder;
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeType& v)
{
   return encoder;
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Era& v)
{
   if (v.IsImmortal)
   {
      encoder << static_cast<const uint8_t>(0x00);
      return encoder;
   }

   const uint64_t quantizeFactor = std::max<uint64_t>(1, v.Period / 4096);
   const uint64_t lastBit = v.Period & (uint64_t)-(int64_t)v.Period;
   const double logOf2 = lastBit != 0 ? std::log2(lastBit) : 64;
   const uint16_t low = static_cast<uint16_t>(std::min(15.0, std::max(1.0, logOf2 - 1)));
   const uint16_t high = static_cast<uint16_t>((v.Phase / quantizeFactor) << 4);
   const uint16_t encoded = low | high;

   encoder << encoded;
   return encoder;
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::AccountId& v)
{
   switch (substrate::constants::AddressVersion)
   {
   case 0:
      encoder << substrate::hex_decode(v.value());
      break;
   case 1:
      encoder << static_cast<const uint8_t>(0xFF) << substrate::hex_decode(v.value());
      break;
   case 2:
      encoder << static_cast<const uint8_t>(0x00) << substrate::hex_decode(v.value());
      break;
   default:
      static_assert(substrate::constants::AddressVersion >= 0 && substrate::constants::AddressVersion <= 2, "not implemented address version");
      break;
   }
   return encoder;
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Extrinsic& v)
{
   encoder << v.Signed;
   encoder << v.TransactionVersion;
   encoder << v.Account;
   encoder << v.Era;
   encoder << v.Nonce;
   encoder << v.Charge;
   encoder << v.Method;
   encoder << v.Signature;
   return encoder;
}
