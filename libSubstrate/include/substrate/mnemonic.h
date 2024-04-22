#pragma once
#include "types.h"
#include "crypto.h"

namespace substrate
{
   namespace mnemonic
   {
      enum class BIP39WordList
      {
         English,
         Japanese,
         Korean,
         Spanish,
         ChineseSimplified,
         ChineseTraditional,
         French,
         Italian,
         Czech,
         Portuguese
      };

      enum class MnemonicSize
      {
         Words12,
         Words15,
         Words18,
         Words21,
         Words24
      };

      [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<std::string> make_mnemonic(MnemonicSize size, BIP39WordList list = BIP39WordList::English);
      [[nodiscard]] LIB_SUBSTRATE_EXPORT std::vector<std::string> make_mnemonic_with_entropy(const substrate::bytes& entropy, BIP39WordList list = BIP39WordList::English);
      [[nodiscard]] LIB_SUBSTRATE_EXPORT substrate::bytes make_secret_from_mnemonic(const std::string& mnemonic, const std::string& password, BIP39WordList list = BIP39WordList::English);
   }

}
