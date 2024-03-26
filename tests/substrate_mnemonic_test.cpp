#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct MnemonicFromEntropyTestParams
{
   substrate::mnemonic::BIP39WordList WordList;
   std::string HexEntropy;
   std::string ExpectedMnemonic;
   std::string Sr25519AccountAddress;
   std::string Ed25519AccountAddress;
};

class MnemonicFromEntropyTest : public testing::TestWithParam<MnemonicFromEntropyTestParams>
{
};

std::string join_vector_accumulate(const std::vector<std::string> &vec)
{
   if (vec.empty())
      return std::string();

   // Start accumulating from the second element, so prepend the first element to the initial value
   return std::accumulate(std::next(vec.begin()), vec.end(), vec[0],
                          [](const std::string &a, const std::string &b)
                          {
                             return a + " " + b;
                          });
}

TEST_P(MnemonicFromEntropyTest, MnemonicFromEntropyTest)
{
   auto params = GetParam();
   const auto entropy = substrate::hex_decode(params.HexEntropy);
   const auto mnemonicList = substrate::mnemonic::make_mnemonic_with_entropy(entropy, params.WordList);
   EXPECT_EQ(join_vector_accumulate(mnemonicList), params.ExpectedMnemonic);

   const std::string password;
   const auto account1 = substrate::make_account_with_mnemonic(substrate::models::KeyType::Sr25519, params.ExpectedMnemonic, params.WordList, password);
   EXPECT_EQ(account1->get_address(), params.Sr25519AccountAddress);

   const auto account2 = substrate::make_account_with_mnemonic(substrate::models::KeyType::Ed25519, params.ExpectedMnemonic, params.WordList, password);
   EXPECT_EQ(account2->get_address(), params.Ed25519AccountAddress);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, MnemonicFromEntropyTest, testing::Values(
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xe56c530cc0bd3bc9c47e74789b111982", "tornado glad segment lift squirrel top ball soldier joy sudden edit advice", "5Fe24e21Ff5vRtuWa4ZNPv1EGQz1zBq1VtT8ojqfmzo9k11P", "5CcaF7yE6YU67TyPHjSwd9DKiVBTAS2AktdxNG3DeLYs63gF"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0x2c1ace5b538b6665dbd209df80f220e87e43888f", "clown stool nothing poem reopen cream hungry donkey test always market special tomorrow session detail", "5EjXrVNGukEPqVDwV1h854h4jhmxso6ifJMH2JB9LGHxCtyw", "5GqEMUKZBJvBDr6Jh2iJ3E3nQ5zAoMVvex7UQdsT7ZB61Tx7"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0x97cb2350a9dd728a898fdf08934101e20f585f5906ee31ee", "oak flip stage father strong earn change winner ancient old document series void cook goat tape cradle indoor", "5FBrLjUNtrjiN73szsVs3cCWS1ZsMAv3qgj1CW7EFztaf2Ud", "5CmMEY9nfxd74NtTGeZkDXTG7s2v9ZHYnUfPws8KpqLuS6vB"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xb45c49d15d8bfa58888aeb61f67db17619dbdb4cf3014b3ff13dd925", "reform time inmate roast sausage clump captain frost giggle recycle hobby umbrella oval unit critic gasp enroll zebra exhaust rather fun", "5Fh4M4vdfEskyo2zch9dYhwoPeyzhK2L1bC5EVtRrWneN7t4", "5Hpe8G5eQanbCYpBnZAzTwzjG5XukfWgC6T9oQgSV6i29XUL"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xe42e88a99a359c4d94a02dfd95877f0955a0ec91a7e9402a12e5fbb2100ae01f", "tomorrow inmate clerk crucial flush chat family aisle work promote thank bargain foam iron educate wood dizzy explain ride wash canal air lesson wish", "5FnynfuwAwGCsBxzNHQ5KfW2gTaJGXjQ6bdKrryDuaD7zodK", "5GtoaENzjxPwxRTmA4dnn79AL4qZtZWq7CtcWh54hEe2B4XC"}
));
