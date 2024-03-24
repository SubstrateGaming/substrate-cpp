#include <substrate/substrate.h>

#include <cmath>
#include <cstdint>
#include <algorithm>

//
// Method
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Method& v)
{
   encoder << v.ModuleIndex;
   encoder << v.CallIndex;
   encoder << v.Parameters;
   return encoder;
}

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Method& v)
{
   decoder >> v.ModuleIndex;
   decoder >> v.CallIndex;
   decoder >> v.Parameters;
   return decoder;
}

substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeType& v)
{
   return encoder;
}

//
// Era
//
uint64_t substrate::models::Era::get_start(uint64_t blockNumber) const
{
   if (IsImmortal)
      return 0ull;

   return ((std::max<uint64_t>(blockNumber, Phase) - Phase) / Period * Period) + Phase;
}

substrate::models::Era substrate::models::Era::make(uint32_t lifeTime, uint64_t finalizedHeaderBlockNumber)
{
   if (lifeTime == static_cast<uint32_t>(0))
      return substrate::models::Era{true, 0ull, 0ull};

    uint64_t period = static_cast<uint64_t>(std::pow(2, std::round(std::log2(static_cast<double>(lifeTime)))));
    period = std::max(period, static_cast<uint64_t>(4));
    period = std::min(period, static_cast<uint64_t>(65536));
    const uint64_t phase = finalizedHeaderBlockNumber % period;
    const uint64_t quantize_factor = std::max(period >> 12, static_cast<uint64_t>(1));
    const uint64_t quantized_phase = (phase / quantize_factor) * quantize_factor;
    return substrate::models::Era{false, period, quantized_phase};
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

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Era& v)
{
   const auto bytes = decoder.bytes();
   if (decoder.size() == 1 && bytes[0] == 0x00)
   {
      v = substrate::models::Era{true, 0ull, 0ull};
      decoder.seek(1);
   }
   else if (decoder.size() == 2)
   {
      const uint64_t ul0 = static_cast<uint64_t>(bytes[0]);
      const uint64_t ul1 = static_cast<uint64_t>(bytes[1]);
      const uint64_t encoded = ul0 + (ul1 << 8);
      const uint64_t period = 2ULL << (encoded % (1 << 4));
      const uint64_t quantizeFactor = std::max(static_cast<uint64_t>(1), period >> 12);
      const uint64_t phase = (encoded >> 4) * quantizeFactor;

      if (period < 4 || phase >= period) {
         throw std::invalid_argument("invalid byte stream to represente Era");
      }
      decoder.seek(2);
      v = substrate::models::Era{false, period, phase};
   }
   else
   {
      throw std::runtime_error("invalid byte stream to decode Era");
   }

   return decoder;
}

//
// AccountId
//
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
