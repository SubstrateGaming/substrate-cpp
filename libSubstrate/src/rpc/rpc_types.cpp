#include <substrate/substrate.h>

using namespace substrate::rpc;

//
// Bytes
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const Bytes& v)
{
   encoder << v.const_value();
   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, Bytes& v)
{
   decoder >> v.value();
   return decoder;
}

void substrate::rpc::to_json(nlohmann::json &j, const Bytes &v)
{
   substrate::encoder encoder;
   encoder << v;
   j = encoder.assemble_hex();
}

void substrate::rpc::from_json(const nlohmann::json &j, Bytes &v)
{
   substrate::decoder decoder(substrate::hex_decode(j.get<std::string>()));
   decoder >> v;
}

//
// Hash
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Hash &v)
{
   encoder << substrate::hex_decode(v.const_value());
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Hash &v)
{
   // If we need that here, we need to make sure we know the hash size in advance?
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const Hash &v)
{
   j = v.const_value();
}

void substrate::rpc::from_json(const nlohmann::json &j, Hash &v)
{
   v = Hash{j.get<std::string>()};
}

//
// StorageKey
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const StorageKey& v)
{
   encoder << substrate::hex_decode(v.const_value());
   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, StorageKey& v)
{
   // If we need that here, we need to make sure we know the storage key size in advance?
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const StorageKey &v)
{
   j = v.const_value();
}

void substrate::rpc::from_json(const nlohmann::json &j, StorageKey &v)
{
   v = StorageKey{j.get<std::string>()};
}

//
// StorageData
//
substrate::encoder& substrate::rpc::operator<<(substrate::encoder& encoder, const StorageData& v)
{
   encoder << substrate::hex_decode(v.const_value());
   return encoder;
}

substrate::decoder& substrate::rpc::operator>>(substrate::decoder& decoder, StorageData& v)
{
   // If we need that here, we need to make sure we know the storage data size in advance?
   throw std::runtime_error("not implemented");
}

void substrate::rpc::to_json(nlohmann::json &j, const StorageData &v)
{
   j = v.const_value();
}

void substrate::rpc::from_json(const nlohmann::json &j, StorageData &v)
{
   v = StorageData{j.get<std::string>()};
}

//
// AccountId
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const AccountId &v)
{
   switch (substrate::constants::AddressVersion)
   {
   case 0:
      encoder << substrate::hex_decode(v.const_value());
      break;
   case 1:
      encoder << static_cast<const uint8_t>(0xFF) << substrate::hex_decode(v.const_value());
      break;
   case 2:
      encoder << static_cast<const uint8_t>(0x00) << substrate::hex_decode(v.const_value());
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

void substrate::rpc::to_json(nlohmann::json &j, const AccountId &v)
{
   // If not encoded in Base58 the RPC would result into the following error message:
   // "Base 58 requirement is violated"
   j = substrate::get_address(substrate::hex_decode(v.const_value()));
}

void substrate::rpc::from_json(const nlohmann::json &j, AccountId &v)
{
   // We do not really need that.
   throw std::runtime_error("not implemented");
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
   encoder << v.Tip;
   encoder << v.AssetId;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, ChargeAssetTxPayment &v)
{
   decoder >> v.Tip;
   decoder >> v.AssetId;
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
   const uint64_t lastBit = v.Period & (uint64_t) - (int64_t)v.Period;
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

      if (period < 4 || phase >= period)
      {
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

   const uint8_t signed_flag{static_cast<uint8_t>((v.Signed ? static_cast<uint8_t>(0x80) : static_cast<uint8_t>(0x00)) + substrate::constants::TransactionVersion)};
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
   v.TransactionVersion = static_cast<uint8_t>(signed_flag - (v.Signed ? static_cast<uint8_t>(0x80) : static_cast<uint8_t>(0x00)));

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
   substrate::encoder encoder;
   encoder << v;
   j = encoder.assemble_hex();
}

void substrate::rpc::from_json(const nlohmann::json &j, Extrinsic &v)
{
   substrate::decoder decoder(substrate::hex_decode(j.get<std::string>()));
   decoder >> v;
}

//
// Block
//
void substrate::rpc::to_json(nlohmann::json &j, const Block &v)
{
   to_json(j["extrinsics"], v.Extrinsics);
   to_json(j["header"], v.Header);
}

void substrate::rpc::from_json(const nlohmann::json &j, Block &v)
{
   from_json(j["extrinsics"], v.Extrinsics);
   from_json(j["header"], v.Header);
}

//
// BlockNumber
//
void substrate::rpc::to_json(nlohmann::json &j, const BlockNumber &v)
{
   to_json(j, v.const_value());
}

void substrate::rpc::from_json(const nlohmann::json &j, BlockNumber &v)
{
   from_json(j, v.value());
}

void substrate::rpc::to_json(nlohmann::json &j, const std::optional<BlockNumber> &v)
{
   if (v.has_value())
      to_json(j, v.value());
   else
      j = nlohmann::json();
}

void substrate::rpc::from_json(const nlohmann::json &j, std::optional<BlockNumber> &v)
{
   if (!j.is_null())
   {
      BlockNumber bn{0};
      from_json(j, bn);
      v = bn;
   }
   else
   {
      v = std::nullopt;
   }
}

//
// SignedBlock
//
void substrate::rpc::to_json(nlohmann::json &j, const SignedBlock &v)
{
   to_json(j["block"], v.Block);
   if (v.Justifications.has_value())
      j["justifications"] = v.Justifications.value();
   else
      j["justifications"] = nlohmann::json();
}

void substrate::rpc::from_json(const nlohmann::json &j, SignedBlock &v)
{
   from_json(j["block"], v.Block);
   if (!j["justifications"].is_null())
   {
      std::vector<Justification> justifications;
      from_json(j["justifications"], justifications);
      v.Justifications = justifications;
   }
   else
   {
      v.Justifications = std::nullopt;
   }
}

//
// Payload::extra_t
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Payload::extra_t &v)
{
   encoder << v.Mortality;
   encoder << v.Nonce;
   encoder << v.Charge;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Payload::extra_t &v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

//
// Payload::additional_t
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Payload::additional_t &v)
{
   encoder << v.SpecVersion;
   encoder << v.TransactionVersion;
   encoder << v.GenesisHash;
   encoder << v.CheckpointHash;
   return encoder;
}

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Payload::additional_t &v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

//
// Payload
//
substrate::encoder &substrate::rpc::operator<<(substrate::encoder &encoder, const Payload &v)
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

substrate::decoder &substrate::rpc::operator>>(substrate::decoder &decoder, Payload &v)
{
   // We do not really need that.
   (void)decoder;
   (void)v;
   throw std::runtime_error("not implemented");
}

Payload Payload::make(const Extrinsic &extrinsic, const Hash &genesis, const Hash &checkpoint, const RuntimeVersion &runtimeVersion)
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
// Health
//
void substrate::rpc::to_json(nlohmann::json &j, const Health &v)
{
   to_json(j["peers"], v.peers);
   to_json(j["isSyncing"], v.isSyncing);
   to_json(j["shouldHavePeers"], v.shouldHavePeers);
}

void substrate::rpc::from_json(const nlohmann::json &j, Health &v)
{
   from_json(j["peers"], v.peers);
   from_json(j["isSyncing"], v.isSyncing);
   from_json(j["shouldHavePeers"], v.shouldHavePeers);
}

//
// SyncState
//
void substrate::rpc::to_json(nlohmann::json &j, const SyncState &v)
{
   to_json(j["currentBlock"], v.currentBlock);
   to_json(j["highestBlock"], v.highestBlock);
   to_json(j["startingBlock"], v.startingBlock);
}

void substrate::rpc::from_json(const nlohmann::json &j, SyncState &v)
{
   from_json(j["currentBlock"], v.currentBlock);
   from_json(j["highestBlock"], v.highestBlock);
   from_json(j["startingBlock"], v.startingBlock);
}

//
// InclusionFee
//
void substrate::rpc::to_json(nlohmann::json &j, const InclusionFee &v)
{
   to_json(j["adjustedWeightFee"], v.adjustedWeightFee);
   to_json(j["baseFee"], v.baseFee);
   to_json(j["lenFee"], v.lenFee);
}

void substrate::rpc::from_json(const nlohmann::json &j, InclusionFee &v)
{
   from_json(j["adjustedWeightFee"], v.adjustedWeightFee);
   from_json(j["baseFee"], v.baseFee);
   from_json(j["lenFee"], v.lenFee);
}

//
// FeeDetails
//
void substrate::rpc::to_json(nlohmann::json &j, const FeeDetails &v)
{
   if (v.inclusionFee.has_value())
      to_json(j["inclusionFee"], v.inclusionFee.value());
   else
      to_json(j["inclusionFee"], nlohmann::json());
}

void substrate::rpc::from_json(const nlohmann::json &j, FeeDetails &v)
{
   if (j["inclusionFee"].is_object())
   {
      InclusionFee inclusionFee;
      from_json(j["inclusionFee"], inclusionFee);
      v.inclusionFee = inclusionFee;
   }
   else
   {
      v.inclusionFee = std::nullopt;
   }
}

//
// RuntimeDispatchInfoV1::Weight
//
void substrate::rpc::to_json(nlohmann::json &j, const RuntimeDispatchInfoV1::Weight &v)
{
   to_json(j["proof_size"], v.proof_size);
   to_json(j["ref_time"], v.ref_time);
}

void substrate::rpc::from_json(const nlohmann::json &j, RuntimeDispatchInfoV1::Weight &v)
{
   from_json(j["proof_size"], v.proof_size);
   from_json(j["ref_time"], v.ref_time);
}

//
// RuntimeDispatchInfoV1
//
void substrate::rpc::to_json(nlohmann::json &j, const RuntimeDispatchInfoV1 &v)
{
   to_json(j["class"], v.classz);
   to_json(j["partialFee"], v.partialFee);
   to_json(j["weight"], v.weight);
}

void substrate::rpc::from_json(const nlohmann::json &j, RuntimeDispatchInfoV1 &v)
{
   from_json(j["class"], v.classz);
   from_json(j["partialFee"], v.partialFee);
   from_json(j["weight"], v.weight);
}

//
// StorageChangeSet
//
void substrate::rpc::to_json(nlohmann::json &j, const StorageChangeSet &v)
{
   to_json(j["block"], v.block);
   to_json(j["changes"], v.changes);
}

void substrate::rpc::from_json(const nlohmann::json &j, StorageChangeSet &v)
{
   from_json(j["block"], v.block);
   from_json(j["changes"], v.changes);
}

//
// ReadProof
//
void substrate::rpc::to_json(nlohmann::json &j, const ReadProof &v)
{
   to_json(j["at"], v.at);
   to_json(j["proof"], v.proof);
}

void substrate::rpc::from_json(const nlohmann::json &j, ReadProof &v)
{
   from_json(j["at"], v.at);
   from_json(j["proof"], v.proof);
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
   // I am not sure why but in RPC the compact integer is encoded differently than expected?!
   // This seems odd but also works.

   if (j.is_string())
   {
      const auto s = j.get<std::string>();
      p = std::stoull(s, nullptr, 16);
   }
   else if (j.is_number_integer())
   {
      // The account index type is simply encoded as is.
      uint64_t value{0};
      from_json(j, value);
      p = value;
   }
   else
   {
      throw std::runtime_error("CompactInteger json representation not expected");
   }
}
