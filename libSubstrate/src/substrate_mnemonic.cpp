#include <substrate/substrate.h>

#include <sodium/crypto_auth_hmacsha512.h>

#include <random>
#include <ctime>
#include <format>
#include <vector>
#include <bitset>
#include <algorithm>

#include "bip39.h"

using namespace substrate::mnemonic;

namespace substrate::mnemonic::detail
{
   const std::vector<std::string> &get_words(BIP39WordList list)
   {
      switch (list)
      {
      case BIP39WordList::English:
         return bip39::kWordsEnglish;
      case BIP39WordList::Japanese:
         return bip39::kWordsJapanese;
      case BIP39WordList::Spanish:
         return bip39::kWordsSpanish;
      case BIP39WordList::ChineseSimplified:
         return bip39::kWordsChineseSimplified;
      case BIP39WordList::ChineseTraditional:
         return bip39::kWordsChineseTraditional;
      case BIP39WordList::French:
         return bip39::kWordsFrench;
      case BIP39WordList::Italian:
         return bip39::kWordsItalian;
      case BIP39WordList::Czech:
         return bip39::kWordsCzech;
      case BIP39WordList::Portuguese:
         return bip39::kWordsPortuguese;
      default:
         break;
      }

      throw std::runtime_error("invalid word list");
   }

   bool is_entropy_valid(size_t size)
   {
      return size == 16 || size == 20 || size == 24 || size == 28 || size == 32;
   }

   int get_word_index(const std::vector<std::string> &wordlist, const std::string &search)
   {
      int index = 0;
      for (const auto &word : wordlist)
      {
         if (word == search)
            return index;

         ++index;
      }
      return -1;
   }

   std::vector<std::string> make_words(const std::string &str)
   {
      std::vector<std::string> result;
      std::istringstream iss(str);
      std::string token;
      while (iss >> token)
      {
         result.push_back(token);
      }
      return result;
   }

   std::string make_bit_string(const bytes &bytes)
   {
      std::string bit_string;
      bit_string.reserve(bytes.size() * 8);

      for (uint8_t byte : bytes)
         bit_string += std::bitset<8>(byte).to_string();

      return bit_string;
   }

   std::string derive_checksum_bits(const std::vector<uint8_t> &entropy_bytes)
   {
      const size_t ent = entropy_bytes.size() * 8;
      const size_t cs = ent / 32;

      const auto hash = substrate::hash::sha256(entropy_bytes);

      std::stringstream result_stream;
      for (auto h : hash)
      {
         result_stream << std::bitset<8>(h).to_string();
      }
      std::string result = result_stream.str();

      return result.substr(0, cs);
   }

   std::vector<std::string> derive_words_from_bit_string(const std::string &bit_string, const std::vector<std::string> &wordlist)
   {
      std::vector<std::string> words;
      size_t num_words = bit_string.length() / 11;

      for (size_t i = 0; i < num_words; ++i)
      {
         std::string bit_segment = bit_string.substr(i * 11, 11);
         std::bitset<11> bitset(bit_segment);
         unsigned long index = bitset.to_ulong();
         words.push_back(wordlist[index]);
      }

      return words;
   }

   std::vector<uint8_t> derive_entropy_from_bit_string(const std::string &bits)
   {
      std::vector<uint8_t> bytes;
      for (size_t i = 0; i < bits.length(); i += 8)
      {
         std::bitset<8> byte(std::string(bits, i, 8));
         bytes.push_back(static_cast<uint8_t>(byte.to_ulong()));
      }
      return bytes;
   }

   std::vector<std::string> make_mnemonic_from_entropy(size_t entropy_size, BIP39WordList list)
   {
      const auto entropy = substrate::utils::make_random_bytes(entropy_size);
      return substrate::mnemonic::make_mnemonic_with_entropy(entropy, list);
   }

   substrate::bytes make_seed_from_entropy(const substrate::bytes& entropy, const std::string& password)
   {
      if (!is_entropy_valid(entropy.size()))
         throw std::runtime_error("invalid mnemonic entropy size");

      std::string salt = std::format("mnemonic{}", password);
      const substrate::bytes salt_bytes(salt.begin(), salt.end());
      const auto result = substrate::pbkdf2_hmac_sha512(64, entropy, salt_bytes, 2048);
      return result;
   }

   substrate::bytes make_entropy_from_mnemonic(const std::string &mnemonic, BIP39WordList list)
   {
      const auto &wordlist = get_words(list);
      const auto words = make_words(mnemonic);
      if (words.size() % 3 != 0)
         throw std::runtime_error("invalid mnemonic");

      std::string bit_string;
      for (const auto &word : words)
      {
         int index = get_word_index(wordlist, word);
         if (index == -1)
            throw std::invalid_argument("invalid mnemonic");

         bit_string += std::bitset<11>(index).to_string();
      }

      // split the binary string into ENT/CS
      int divider_index = bit_string.length() / 33 * 32;
      const auto entropy_bits = bit_string.substr(0, divider_index);
      const auto checksum_bits = bit_string.substr(divider_index);

      // calculate the checksum and compare
      const auto entropy = derive_entropy_from_bit_string(entropy_bits);

      if (!is_entropy_valid(entropy.size()))
      {
         throw std::runtime_error("invalid mnemonic entropy size");
      }

      const auto new_checksum = derive_checksum_bits(entropy);
      if (new_checksum != checksum_bits)
         throw std::runtime_error("invalid mnemonic checksum");

      return entropy;
   }
}

std::vector<std::string> substrate::mnemonic::make_mnemonic(MnemonicSize size, BIP39WordList list)
{
   switch (size)
   {
   case MnemonicSize::Words12:
      return detail::make_mnemonic_from_entropy(16, list);
   case MnemonicSize::Words15:
      return detail::make_mnemonic_from_entropy(20, list);
   case MnemonicSize::Words18:
      return detail::make_mnemonic_from_entropy(24, list);
   case MnemonicSize::Words21:
      return detail::make_mnemonic_from_entropy(28, list);
   case MnemonicSize::Words24:
      return detail::make_mnemonic_from_entropy(32, list);
   default:
      break;
   }

   throw std::runtime_error("invalid mnemonic size");
}

std::vector<std::string> substrate::mnemonic::make_mnemonic_with_entropy(const substrate::bytes &entropy, BIP39WordList list)
{
   if (!detail::is_entropy_valid(entropy.size()))
   {
      throw std::runtime_error("invalid mnemonic entropy size");
   }

   auto bit_string = substrate::mnemonic::detail::make_bit_string(entropy);
   bit_string += substrate::mnemonic::detail::derive_checksum_bits(entropy);

   return substrate::mnemonic::detail::derive_words_from_bit_string(bit_string, substrate::mnemonic::detail::get_words(list));
}

substrate::bytes substrate::mnemonic::make_secret_from_mnemonic(const std::string &mnemonic, const std::string &password, BIP39WordList list)
{
   const auto entropy = detail::make_entropy_from_mnemonic(mnemonic, list);
   const auto seed = detail::make_seed_from_entropy(entropy, password);
   assert(seed.size() >= 32);
   return substrate::bytes(seed.begin(), seed.begin() + 32);
}