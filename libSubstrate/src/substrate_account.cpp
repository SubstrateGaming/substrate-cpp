#include <substrate/substrate.h>

using namespace substrate::models;

class substrate_account final : public substrate::IAccount
{
   const substrate::models::KeyType _type;
   const substrate::Crypto _crypto;
   const substrate::ICrypto::key_pair _key_pair;

public:
   substrate_account(substrate::models::KeyType type, const std::vector<uint8_t> &seed)
      : _type(type)
      , _crypto(substrate::make_crypto(_type))
      , _key_pair(_crypto->make_keypair(seed))
   {
   }
   virtual ~substrate_account() override = default;

   std::vector<uint8_t> sign(const std::vector<uint8_t> &message) const override
   {
      return _crypto->sign(message, _key_pair);
   }

   bool verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const override
   {
      return _crypto->verify(message, signature, get_public_key());
   }

   const std::vector<uint8_t>& get_public_key() const override { return _key_pair.public_key; }
   substrate::models::AccountId32 get_account_id() const override { return substrate::models::AccountId32(substrate::hex_encode(get_public_key())); }
   std::string get_address() const override { return substrate::get_address(get_public_key()); }

   uint16_t get_address_network() const override
   {
      uint16_t network{0};
      (void)substrate::get_public_key_with_network(get_address(), network);
      return network;
   }

};

substrate::Account substrate::make_account(substrate::models::KeyType type, const std::vector<uint8_t> &seed)
{
   return std::make_shared<substrate_account>(type, seed);
}

substrate::Account substrate::development::make_account_alice()
{
   return substrate::make_account(substrate::models::KeyType::Sr25519, substrate::hex_decode("0xe5be9a5092b81bca64be81d212e7f2f9eba183bb7a90954f7b76361f6edb5c0a"));
}

substrate::Account substrate::development::make_account_bob()
{
   return substrate::make_account(substrate::models::KeyType::Sr25519, substrate::hex_decode("0x398f0c28f98885e046333d4a41c19cee4c37368a9832c6502f6cfd182e2aef89"));
}
