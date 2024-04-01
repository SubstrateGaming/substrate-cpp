#include <substrate/substrate.h>

using namespace substrate::rpc;

//
// Hash
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Hash &v)
{
   encoder << substrate::hex_decode(v.value());
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Hash &v)
{
   // If we need that, we need to make sure we know the hash size in advance?
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const Hash &v)
{
   j = v.value();
}

void substrate::rpc::from_json(const nlohmann::json &j, Hash &v)
{
   v = Hash{ j.get<std::string>() };
}

//
// AccountId
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const AccountId &v)
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

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, AccountId &v)
{
   uint8_t tmp{0};
   substrate::bytes account_id32(32);

   switch (substrate::constants::AddressVersion)
   {
   case 0:
      decoder >> account_id32;
      v = AccountId(substrate::hex_encode(account_id32));
      break;
   case 1:
      decoder >> tmp;
      decoder >> account_id32;
      v = AccountId(substrate::hex_encode(account_id32));
      break;
   case 2:
      decoder >> tmp;
      decoder >> account_id32;
      v = AccountId(substrate::hex_encode(account_id32));
      break;
   default:
      throw std::runtime_error("invalid account version");
   }
   return decoder;
}

//
// Digest
//
void substrate::rpc::to_json(nlohmann::json &j, const Digest &v)
{
   to_json(j["logs"], v.Logs);
}

void substrate::rpc::from_json(const nlohmann::json &j, Digest &v)
{
   from_json(j["logs"], v.Logs);
}

//
// Header
//
void substrate::rpc::to_json(nlohmann::json &j, const Header &v)
{
   j = nlohmann::json::object();
   to_json(j["number"], v.number);
   to_json(j["extrinsicsRoot"], v.extrinsicsRoot);
   to_json(j["parentHash"], v.parentHash);
   to_json(j["stateRoot"], v.stateRoot);
   to_json(j["digest"], v.digest);
}

void substrate::rpc::from_json(const nlohmann::json &j, Header &v)
{
   v = Header{};
   from_json(j["number"], v.number);
   from_json(j["extrinsicsRoot"], v.extrinsicsRoot);
   from_json(j["parentHash"], v.parentHash);
   from_json(j["stateRoot"], v.stateRoot);
   from_json(j["digest"], v.digest);
}

//
// ChargeAssetTxPayment
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const ChargeAssetTxPayment &v)
{
   encoder << v.AssetId;
   encoder << v.Tip;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, ChargeAssetTxPayment &v)
{
   decoder >> v.AssetId;
   decoder >> v.Tip;
   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const ChargeAssetTxPayment &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, ChargeAssetTxPayment &v)
{
   throw std::runtime_error("not implemented");
}

//
// ChargeTransactionPayment
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const ChargeTransactionPayment &v)
{
   encoder << v.Tip;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, ChargeTransactionPayment &v)
{
   decoder >> v.Tip;
   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const ChargeTransactionPayment &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, ChargeTransactionPayment &v)
{
   throw std::runtime_error("not implemented");
}

//
// Signature
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Signature &v)
{
   encoder << static_cast<uint8_t>(v.Type);
   encoder << v.Bytes;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Signature &v)
{
   uint8_t tmp{0};
   decoder >> tmp;

   v.Type = static_cast<KeyType>(tmp);
   v.Bytes.resize(64);

   decoder >> v.Bytes;
   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const Signature &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, Signature &v)
{
   throw std::runtime_error("not implemented");
}

//
// Era
//
uint64_t Era::get_start(uint64_t blockNumber) const
{
   if (IsImmortal)
      return 0ull;

   return ((std::max<uint64_t>(blockNumber, Phase) - Phase) / Period * Period) + Phase;
}

Era Era::make(uint32_t lifeTime, CompactInteger finalizedHeaderBlockNumber)
{
   if (lifeTime == static_cast<uint32_t>(0))
      return Era{true, 0ull, 0ull};

    uint64_t period = static_cast<uint64_t>(std::pow(2, std::round(std::log2(static_cast<double>(lifeTime)))));
    period = std::max(period, static_cast<uint64_t>(4));
    period = std::min(period, static_cast<uint64_t>(65536));
    const uint64_t phase = static_cast<uint64_t>(finalizedHeaderBlockNumber) % period;
    const uint64_t quantize_factor = std::max(period >> 12, static_cast<uint64_t>(1));
    const uint64_t quantized_phase = (phase / quantize_factor) * quantize_factor;
    return Era{false, period, quantized_phase};
}

substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Era &v)
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

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Era &v)
{
   uint8_t first{0};
   decoder >> first;

   if (first == 0x00)
   {
      v = Era{true, 0ull, 0ull};
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
      v = Era{false, period, phase};
   }

   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const Era &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, Era &v)
{
   throw std::runtime_error("not implemented");
}

//
// Method
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Method &v)
{
   encoder << v.ModuleIndex;
   encoder << v.CallIndex;
   encoder << v.Parameters;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Method &v)
{
   decoder >> v.ModuleIndex;
   decoder >> v.CallIndex;
   decoder >> v.Parameters;
   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const Method &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, Method &v)
{
   throw std::runtime_error("not implemented");
}

//
// Extrinsic
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Extrinsic &v)
{
   substrate::encoder sub;

   const uint8_t signed_flag{ static_cast<uint8_t>((v.Signed ? static_cast<uint8_t>(0x80) : static_cast<uint8_t>(0x00)) + substrate::constants::TransactionVersion) };
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

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Extrinsic &v)
{
   v = Extrinsic{};

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

void substrate::rpc::to_json(nlohmann::json &j, const Extrinsic &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, Extrinsic &v)
{
   throw std::runtime_error("not implemented");
}

//
// Block
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Block &v)
{
   throw std::runtime_error("not implemented");
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Block &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const Block &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, Block &v)
{
   throw std::runtime_error("not implemented");
}

//
// BlockNumber
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const BlockNumber &v)
{
   throw std::runtime_error("not implemented");
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, BlockNumber &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const BlockNumber &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, BlockNumber &v)
{
   throw std::runtime_error("not implemented");
}

//
// SignedBlock
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const SignedBlock &v)
{
   throw std::runtime_error("not implemented");
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, SignedBlock &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const SignedBlock &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::from_json(const nlohmann::json &j, SignedBlock &v)
{
   throw std::runtime_error("not implemented");
}

//
// Payload::extra_t
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const Payload::extra_t& v)
{
   encoder << v.Mortality;
   encoder << v.Nonce;
   encoder << v.Charge;
   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, Payload::extra_t& v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

//
// Payload::additional_t
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const Payload::additional_t& v)
{
   encoder << v.SpecVersion;
   encoder << v.TransactionVersion;
   encoder << v.GenesisHash;
   encoder << v.CheckpointHash;
   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, Payload::additional_t& v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

//
// Payload
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const Payload& v)
{
   substrate::encoder sub;
   sub << v.Call;
   sub << v.Extra;
   sub << v.Additional;

   const auto encoded = sub.assemble();
   if (encoded.size() > 256)
      encoder << substrate::hash::blake2(encoded, 256);
   else
      encoder << encoded;

   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, Payload& v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

Payload Payload::make(const Extrinsic& extrinsic, const Hash& genesis, const Hash& checkpoint, const RuntimeVersion& runtimeVersion)
{
   Payload payload;
   payload.Call = extrinsic.Method;
   payload.Extra.Charge = extrinsic.Charge;
   payload.Extra.Mortality = extrinsic.Era;
   payload.Extra.Nonce = extrinsic.Nonce;

   payload.Additional.GenesisHash = genesis;
   payload.Additional.CheckpointHash = checkpoint;

   payload.Additional.SpecVersion = runtimeVersion.specVersion;
   payload.Additional.TransactionVersion = runtimeVersion.transactionVersion;

   return payload;
}

//
// RuntimeVersion
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const RuntimeVersion &v)
{
   throw std::runtime_error("not implemented");
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, RuntimeVersion &v)
{
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const RuntimeVersion &v)
{
  to_json(j["authoringVersion"], v.authoringVersion);
  to_json(j["implVersion"], v.implVersion);
  to_json(j["specVersion"], v.specVersion);
  to_json(j["transactionVersion"], v.transactionVersion);
  to_json(j["implName"], v.implName);
  to_json(j["specName"], v.specName);
}

void substrate::rpc::from_json(const nlohmann::json &j, RuntimeVersion &v)
{
  from_json(j["authoringVersion"], v.authoringVersion);
  from_json(j["implVersion"], v.implVersion);
  from_json(j["specVersion"], v.specVersion);
  from_json(j["transactionVersion"], v.transactionVersion);
  from_json(j["implName"], v.implName);
  from_json(j["specName"], v.specName);
}

//
// Bytes
//
void substrate::rpc::to_json(nlohmann::json &j, const Bytes &p)
{
   j = substrate::hex_encode(p);
}

void substrate::rpc::from_json(const nlohmann::json &j, Bytes &p)
{
   p = substrate::hex_decode(j.get<std::string>());
}

//
// CompactInteger
//
void substrate::rpc::to_json(nlohmann::json &j, const CompactInteger &p)
{
   substrate::encoder encoder;
   encoder << p;
   j = encoder.assemble_hex();
}

void substrate::rpc::from_json(const nlohmann::json &j, CompactInteger &p)
{
   substrate::decoder decoder(substrate::hex_decode(j.get<std::string>()));
   decoder >> p;
}