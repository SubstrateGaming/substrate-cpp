#pragma once
#include "types.h"
#include "models/keytype.h"

namespace substrate
{
   class LIB_SUBSTRATE_EXPORT IAccount
   {
   public:
      virtual ~IAccount() = default;

      [[nodiscard]] virtual std::vector<uint8_t> sign(const std::vector<uint8_t> &message) const = 0;
      [[nodiscard]] virtual bool verify(const std::vector<uint8_t> &message, const std::vector<uint8_t> &signature) const = 0;

      [[nodiscard]] virtual substrate::models::KeyType get_type() const = 0;
      [[nodiscard]] virtual const std::vector<uint8_t>& get_public_key() const = 0;
      [[nodiscard]] virtual substrate::models::AccountId32 get_account_id() const = 0;
      [[nodiscard]] virtual std::string get_address() const = 0;
      [[nodiscard]] virtual uint16_t get_address_network() const = 0;
   };
   using Account = std::shared_ptr<IAccount>;

   [[nodiscard]] LIB_SUBSTRATE_EXPORT Account make_account(substrate::models::KeyType type, const std::vector<uint8_t> &seed);

   // Development
   namespace development
   {
      [[nodiscard]] LIB_SUBSTRATE_EXPORT Account make_account_alice();
      [[nodiscard]] LIB_SUBSTRATE_EXPORT Account make_account_bob();
   }
}
