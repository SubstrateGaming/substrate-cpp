#include <substrate/substrate.h>

#include <cmath>
#include <cstdint>
#include <algorithm>


namespace substrate::models
{
   Payload make_payload(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion)
   {
      substrate::models::Payload payload;
      payload.Call = extrinsic.Method;
      payload.Extra.Charge = extrinsic.Charge;
      payload.Extra.Mortality = extrinsic.Era;
      payload.Extra.Nonce = extrinsic.Nonce;

      payload.Additional.GenesisHash = genesis;
      payload.Additional.CheckpointHash = checkpoint;

      payload.Additional.SpecVersion = runtimeVersion.SpecVersion;
      payload.Additional.TransactionVersion = runtimeVersion.TransactionVersion;

      return payload;
   }
}

//
// Hash
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Hash& v)
{
   encoder << substrate::hex_decode(v.value());
   return encoder;
}

//
// BlockNumber
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::BlockNumber& v)
{
   encoder << v.value();
   return encoder;
}

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::BlockNumber& v)
{
   static_assert(sizeof(substrate::models::BlockNumber) == sizeof(uint32_t), "BlockNumber must be the same size as uint32_t");

   uint32_t value{0ull};
   decoder >> value;
   v = substrate::models::BlockNumber{value};

   return decoder;
}

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

//
// ChargeAssetTxPayment
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeAssetTxPayment& v)
{
   encoder << v.AssetId;
   encoder << v.Tip;
   return encoder;
}

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::ChargeAssetTxPayment& v)
{
   decoder >> v.AssetId;
   decoder >> v.Tip;
   return decoder;
}

//
// ChargeTransactionPayment
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::ChargeTransactionPayment& v)
{
   encoder << v.Tip;
   return encoder;
}

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::ChargeTransactionPayment& v)
{
   decoder >> v.Tip;
   return decoder;
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
   uint8_t first{0};
   decoder >> first;

   if (first == 0x00)
   {
      v = substrate::models::Era{true, 0ull, 0ull};
   }
   else
   {
      uint8_t second{0};
      decoder >> second;

      const uint64_t ul0 = static_cast<uint64_t>(first);
      const uint64_t ul1 = static_cast<uint64_t>(second);
      const uint64_t encoded = ul0 + (ul1 << 8);
      const uint64_t period = 2ULL << (encoded % (1 << 4));
      const uint64_t quantizeFactor = std::max(static_cast<uint64_t>(1), period >> 12);
      const uint64_t phase = (encoded >> 4) * quantizeFactor;

      if (period < 4 || phase >= period) {
         throw std::invalid_argument("invalid byte stream to represente Era");
      }
      v = substrate::models::Era{false, period, phase};
   }

   return decoder;
}

//
// AccountId32
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::AccountId32& v)
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

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::AccountId32& v)
{
   uint8_t tmp{0};
   std::vector<uint8_t> account_id32(32);

   switch (substrate::constants::AddressVersion)
   {
   case 0:
      decoder >> account_id32;
      v = substrate::models::AccountId32(substrate::hex_encode(account_id32));
      break;
   case 1:
      decoder >> tmp;
      decoder >> account_id32;
      v = substrate::models::AccountId32(substrate::hex_encode(account_id32));
      break;
   case 2:
      decoder >> tmp;
      decoder >> account_id32;
      v = substrate::models::AccountId32(substrate::hex_encode(account_id32));
      break;
   default:
      throw std::runtime_error("invalid account version");
   }
   return decoder;
}

//
// Signature
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Signature& v)
{
   encoder << static_cast<uint8_t>(v.Type);
   encoder << v.Bytes;
   return encoder;
}

substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Signature& v)
{
   uint8_t tmp{0};
   decoder >> tmp;

   v.Type = static_cast<substrate::models::KeyType>(tmp);
   v.Bytes.resize(64);

   decoder >> v.Bytes;
   return decoder;
}

//
// Payload::extra_t
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload::extra_t& v)
{
   encoder << v.Mortality;
   encoder << v.Nonce;
   encoder << v.Charge;
   return encoder;
}

//
// Payload::additional_t
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload::additional_t& v)
{
   encoder << v.SpecVersion;
   encoder << v.TransactionVersion;
   encoder << v.GenesisHash;
   encoder << v.CheckpointHash;
   return encoder;
}

//
// Payload
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Payload& v)
{
   substrate::encoder sub;
   sub << v.Call;
   sub << v.Extra;
   sub << v.Additional;

   const auto encoded = sub.assemble();
   if (encoded.size() > 256)
      encoder << substrate::blake2(encoded, 256);
   else
      encoder << encoded;

   return encoder;
}

//
// Extrinsic
//
substrate::encoder& operator<<(substrate::encoder& encoder, const substrate::models::Extrinsic& v)
{
   substrate::encoder sub;

   const uint8_t signed_flag{ static_cast<uint8_t>((v.Signed ? static_cast<uint8_t>(0x80) : static_cast<uint8_t>(0x00)) + substrate::constants::ExtrinsicVersion) };
   sub << signed_flag;

   if (v.Signed)
   {
      sub << v.Account;
      sub << v.Signature;
      sub << v.Era;
      sub << v.Nonce;
      sub << v.Charge;
   }

   sub << v.Method;
   encoder << sub;

   return encoder;
}

 substrate::decoder& operator>>(substrate::decoder& decoder, substrate::models::Extrinsic& v)
 {
   v = substrate::models::Extrinsic{};

   // Decode length
   substrate::CompactInteger length{0};
   decoder >> length;

   // Decode signed_flag
   uint8_t signed_flag{0};
   decoder >> signed_flag;

   v.Signed = signed_flag >= 0x80;
   v.TransactionVersion = static_cast<uint8_t>(signed_flag - (v.Signed ?  static_cast<uint8_t>(0x80) : static_cast<uint8_t>(0x00)));

   if (v.Signed)
   {
      decoder >> v.Account;
      decoder >> v.Signature;
      decoder >> v.Era;
      decoder >> v.Nonce;
      decoder >> v.Charge;
   }

   decoder >> v.Method;

   assert(decoder.remaining_bytes() == 0);
   return decoder;
 }
