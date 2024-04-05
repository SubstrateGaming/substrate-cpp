#pragma once

#include <string>
#include <vector>

namespace substrate::mnemonic::detail
{
   class bip39
   {
   public:
      static const std::vector<std::string> kWordsEnglish;
      static const std::vector<std::string> kWordsChineseSimplified;
      static const std::vector<std::string> kWordsChineseTraditional;
      static const std::vector<std::string> kWordsFrench;
      static const std::vector<std::string> kWordsJapanese;
      static const std::vector<std::string> kWordsSpanish;
      static const std::vector<std::string> kWordsPortuguese;
      static const std::vector<std::string> kWordsCzech;
      static const std::vector<std::string> kWordsItalian;
   };
}
