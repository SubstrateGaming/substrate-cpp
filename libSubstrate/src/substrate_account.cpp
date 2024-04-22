#include <substrate/substrate.h>

class substrate_account final : public substrate::IAccount
{
   const substrate::rpc::KeyType _type;
   const substrate::Crypto _crypto;
   const substrate::ICrypto::key_pair _key_pair;

public:
   substrate_account(substrate::rpc::KeyType type, const substrate::bytes &seed)
      : _type(type)
      , _crypto(substrate::make_crypto(_type))
      , _key_pair(_crypto->make_keypair(seed))
   {
   }
   virtual ~substrate_account() override = default;

   substrate::bytes sign(const substrate::bytes &message) const override
   {
      return _crypto->sign(message, _key_pair);
   }

   bool verify(const substrate::bytes &message, const substrate::bytes &signature) const override
   {
      return _crypto->verify(message, signature, get_public_key());
   }

   substrate::rpc::KeyType get_type() const override { return _type; }
   const substrate::bytes& get_public_key() const override { return _key_pair.public_key; }
   substrate::rpc::AccountId get_account_id() const override { return substrate::rpc::AccountId(substrate::hex_encode(get_public_key())); }
   std::string get_address() const override { return substrate::get_address(get_public_key()); }

   uint16_t get_address_network() const override
   {
      uint16_t network{0};
      (void)substrate::get_public_key_with_network(get_address(), network);
      return network;
   }

};

substrate::Account substrate::make_account(substrate::rpc::KeyType type, const substrate::bytes &seed)
{
   switch (type)
   {
   case substrate::rpc::KeyType::Sr25519:
   case substrate::rpc::KeyType::Ed25519:
      return std::make_shared<substrate_account>(type, seed);
   default:
      break;
   }
   throw std::runtime_error("invalid key type");
}

substrate::Account substrate::make_account_with_mnemonic(substrate::rpc::KeyType type, const std::string& mnemonic, substrate::mnemonic::BIP39WordList list, const std::string& password)
{
   return substrate::make_account(type, substrate::mnemonic::make_secret_from_mnemonic(mnemonic, password, list));
}

substrate::Account substrate::development::make_account_alice()
{
   return substrate::make_account(substrate::rpc::KeyType::Sr25519, substrate::hex_decode("0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a"));
}

substrate::Account substrate::development::make_account_bob()
{
   return substrate::make_account(substrate::rpc::KeyType::Sr25519, substrate::hex_decode("0x398f0c28f98885e046333d4a41c19cee4c37368a9832c6502f6cfd182e2aef89"));
}
