#pragma once
#include "types.h"
#include "mnemonic.h"
#include "rpc_types.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT IAccount
   {
   public:
      virtual ~IAccount() = default;

      [[nodiscard]] virtual substrate::bytes sign(const substrate::bytes &message) const = 0;
      [[nodiscard]] virtual bool verify(const substrate::bytes &message, const substrate::bytes &signature) const = 0;

      [[nodiscard]] virtual substrate::rpc::KeyType get_type() const = 0;
      [[nodiscard]] virtual const substrate::bytes& get_public_key() const = 0;
      [[nodiscard]] virtual substrate::rpc::AccountId get_account_id() const = 0;
      [[nodiscard]] virtual std::string get_address() const = 0;
      [[nodiscard]] virtual uint16_t get_address_network() const = 0;
   };
   using Account = std::shared_ptr<IAccount>;

   LIB_SUBSTRATE_EXPORT [[nodiscard]] Account make_account(substrate::rpc::KeyType type, const substrate::bytes &seed);
   LIB_SUBSTRATE_EXPORT [[nodiscard]] Account make_account_with_mnemonic(substrate::rpc::KeyType type, const std::string& mnemonic, substrate::mnemonic::BIP39WordList list = substrate::mnemonic::BIP39WordList::English, const std::string& password = std::string());

   // Development
   namespace development
   {
      LIB_SUBSTRATE_EXPORT [[nodiscard]] Account make_account_alice();
      LIB_SUBSTRATE_EXPORT [[nodiscard]] Account make_account_bob();
   }
}
