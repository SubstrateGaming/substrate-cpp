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

struct MnemonicSeedAndMiniSecretTestParams
{
   std::string Mnemonic;
   std::string ExpectedEntropy;
   std::string ExpectedSeed;
};

class MnemonicFromEntropyTest : public testing::TestWithParam<MnemonicFromEntropyTestParams>
{
};

class MnemonicSeedAndMiniSecretTest : public testing::TestWithParam<MnemonicSeedAndMiniSecretTestParams>
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

namespace substrate::mnemonic::detail
{
   // Forward
   substrate::bytes make_entropy_from_mnemonic(const std::string &mnemonic, BIP39WordList list);
   substrate::bytes make_seed_from_entropy(const substrate::bytes& entropy, const std::string& password);
}

TEST_P(MnemonicSeedAndMiniSecretTest, MnemonicSeedAndMiniSecretTest)
{
   auto params = GetParam();
   const auto type = substrate::mnemonic::BIP39WordList::English;
   const auto password = std::string("Substrate");

   const auto entropy = substrate::mnemonic::detail::make_entropy_from_mnemonic(params.Mnemonic, type);
   const auto seed = substrate::mnemonic::detail::make_seed_from_entropy(entropy, password);

   EXPECT_EQ(entropy, substrate::hex_decode(params.ExpectedEntropy));
   EXPECT_EQ(seed, substrate::hex_decode(params.ExpectedSeed));
}

TEST_P(MnemonicFromEntropyTest, MnemonicFromEntropyTest)
{
   auto params = GetParam();
   const auto entropy = substrate::hex_decode(params.HexEntropy);
   const auto mnemonicList = substrate::mnemonic::make_mnemonic_with_entropy(entropy, params.WordList);
   EXPECT_EQ(join_vector_accumulate(mnemonicList), params.ExpectedMnemonic);

   const std::string password;
   const auto account1 = substrate::make_account_with_mnemonic(substrate::rpc::KeyType::Sr25519, params.ExpectedMnemonic, params.WordList, password);
   EXPECT_EQ(account1->get_address(), params.Sr25519AccountAddress);

   const auto account2 = substrate::make_account_with_mnemonic(substrate::rpc::KeyType::Ed25519, params.ExpectedMnemonic, params.WordList, password);
   EXPECT_EQ(account2->get_address(), params.Ed25519AccountAddress);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, MnemonicFromEntropyTest, testing::Values(
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xe56c530cc0bd3bc9c47e74789b111982", "tornado glad segment lift squirrel top ball soldier joy sudden edit advice", "5Fe24e21Ff5vRtuWa4ZNPv1EGQz1zBq1VtT8ojqfmzo9k11P", "5CcaF7yE6YU67TyPHjSwd9DKiVBTAS2AktdxNG3DeLYs63gF"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0x2c1ace5b538b6665dbd209df80f220e87e43888f", "clown stool nothing poem reopen cream hungry donkey test always market special tomorrow session detail", "5EjXrVNGukEPqVDwV1h854h4jhmxso6ifJMH2JB9LGHxCtyw", "5GqEMUKZBJvBDr6Jh2iJ3E3nQ5zAoMVvex7UQdsT7ZB61Tx7"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0x97cb2350a9dd728a898fdf08934101e20f585f5906ee31ee", "oak flip stage father strong earn change winner ancient old document series void cook goat tape cradle indoor", "5FBrLjUNtrjiN73szsVs3cCWS1ZsMAv3qgj1CW7EFztaf2Ud", "5CmMEY9nfxd74NtTGeZkDXTG7s2v9ZHYnUfPws8KpqLuS6vB"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xb45c49d15d8bfa58888aeb61f67db17619dbdb4cf3014b3ff13dd925", "reform time inmate roast sausage clump captain frost giggle recycle hobby umbrella oval unit critic gasp enroll zebra exhaust rather fun", "5Fh4M4vdfEskyo2zch9dYhwoPeyzhK2L1bC5EVtRrWneN7t4", "5Hpe8G5eQanbCYpBnZAzTwzjG5XukfWgC6T9oQgSV6i29XUL"},
   MnemonicFromEntropyTestParams{substrate::mnemonic::BIP39WordList::English, "0xe42e88a99a359c4d94a02dfd95877f0955a0ec91a7e9402a12e5fbb2100ae01f", "tomorrow inmate clerk crucial flush chat family aisle work promote thank bargain foam iron educate wood dizzy explain ride wash canal air lesson wish", "5FnynfuwAwGCsBxzNHQ5KfW2gTaJGXjQ6bdKrryDuaD7zodK", "5GtoaENzjxPwxRTmA4dnn79AL4qZtZWq7CtcWh54hEe2B4XC"}
));

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, MnemonicSeedAndMiniSecretTest, testing::Values(
   MnemonicSeedAndMiniSecretTestParams{ "abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon about", "0x00000000000000000000000000000000", "0x44e9d125f037ac1d51f0a7d3649689d422c2af8b1ec8e00d71db4d7bf6d127e33f50c3d5c84fa3e5399c72d6cbbbbc4a49bf76f76d952f479d74655a2ef2d453" },
   MnemonicSeedAndMiniSecretTestParams{ "legal winner thank year wave sausage worth useful legal winner thank yellow", "0x7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f", "0x4313249608fe8ac10fd5886c92c4579007272cb77c21551ee5b8d60b780416850f1e26c1f4b8d88ece681cb058ab66d6182bc2ce5a03181f7b74c27576b5c8bf" },
   MnemonicSeedAndMiniSecretTestParams{ "letter advice cage absurd amount doctor acoustic avoid letter advice cage above", "0x80808080808080808080808080808080", "0x27f3eb595928c60d5bc91a4d747da40ed236328183046892ed6cd5aa9ae38122acd1183adf09a89839acb1e6eaa7fb563cc958a3f9161248d5a036e0d0af533d" },
   MnemonicSeedAndMiniSecretTestParams{ "zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo wrong", "0xffffffffffffffffffffffffffffffff", "0x227d6256fd4f9ccaf06c45eaa4b2345969640462bbb00c5f51f43cb43418c7a753265f9b1e0c0822c155a9cabc769413ecc14553e135fe140fc50b6722c6b9df" },
   MnemonicSeedAndMiniSecretTestParams{ "abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon agent", "0x000000000000000000000000000000000000000000000000", "0x44e9d125f037ac1d51f0a7d3649689d422c2af8b1ec8e00d71db4d7bf6d127e33f50c3d5c84fa3e5399c72d6cbbbbc4a49bf76f76d952f479d74655a2ef2d453" },
   MnemonicSeedAndMiniSecretTestParams{ "legal winner thank year wave sausage worth useful legal winner thank year wave sausage worth useful legal will", "0x7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f", "0xcb1d50e14101024a88905a098feb1553d4306d072d7460e167a60ccb3439a6817a0afc59060f45d999ddebc05308714733c9e1e84f30feccddd4ad6f95c8a445" },
   MnemonicSeedAndMiniSecretTestParams{ "letter advice cage absurd amount doctor acoustic avoid letter advice cage absurd amount doctor acoustic avoid letter always", "0x808080808080808080808080808080808080808080808080", "0x9ddecf32ce6bee77f867f3c4bb842d1f0151826a145cb4489598fe71ac29e3551b724f01052d1bc3f6d9514d6df6aa6d0291cfdf997a5afdb7b6a614c88ab36a" },
   MnemonicSeedAndMiniSecretTestParams{ "zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo when", "0xffffffffffffffffffffffffffffffffffffffffffffffff", "0x8971cb290e7117c64b63379c97ed3b5c6da488841bd9f95cdc2a5651ac89571e2c64d391d46e2475e8b043911885457cd23e99a28b5a18535fe53294dc8e1693" },
   MnemonicSeedAndMiniSecretTestParams{ "abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon art", "0x0000000000000000000000000000000000000000000000000000000000000000", "0x44e9d125f037ac1d51f0a7d3649689d422c2af8b1ec8e00d71db4d7bf6d127e33f50c3d5c84fa3e5399c72d6cbbbbc4a49bf76f76d952f479d74655a2ef2d453" },
   MnemonicSeedAndMiniSecretTestParams{ "legal winner thank year wave sausage worth useful legal winner thank year wave sausage worth useful legal winner thank year wave sausage worth title", "0x7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f7f", "0x3037276a5d05fcd7edf51869eb841bdde27c574dae01ac8cfb1ea476f6bea6ef57ab9afe14aea1df8a48f97ae25b37d7c8326e49289efb25af92ba5a25d09ed3" },
   MnemonicSeedAndMiniSecretTestParams{ "letter advice cage absurd amount doctor acoustic avoid letter advice cage absurd amount doctor acoustic avoid letter advice cage absurd amount doctor acoustic bless", "0x8080808080808080808080808080808080808080808080808080808080808080", "0x2c9c6144a06ae5a855453d98c3dea470e2a8ffb78179c2e9eb15208ccca7d831c97ddafe844ab933131e6eb895f675ede2f4e39837bb5769d4e2bc11df58ac42" },
   MnemonicSeedAndMiniSecretTestParams{ "zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo zoo vote", "0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff", "0x047e89ef7739cbfe30da0ad32eb1720d8f62441dd4f139b981b8e2d0bd412ed4eb14b89b5098c49db2301d4e7df4e89c21e53f345138e56a5e7d63fae21c5939" },
   MnemonicSeedAndMiniSecretTestParams{ "ozone drill grab fiber curtain grace pudding thank cruise elder eight picnic", "0x9e885d952ad362caeb4efe34a8e91bd2", "0xf4956be6960bc145cdab782e649a5056598fd07cd3f32ceb73421c3da27833241324dc2c8b0a4d847eee457e6d4c5429f5e625ece22abaa6a976e82f1ec5531d" },
   MnemonicSeedAndMiniSecretTestParams{ "gravity machine north sort system female filter attitude volume fold club stay feature office ecology stable narrow fog", "0x6610b25967cdcca9d59875f5cb50b0ea75433311869e930b", "0xfbcc5229ade0c0ff018cb7a329c5459f91876e4dde2a97ddf03c832eab7f26124366a543f1485479c31a9db0d421bda82d7e1fe562e57f3533cb1733b001d84d" },
   MnemonicSeedAndMiniSecretTestParams{ "hamster diagram private dutch cause delay private meat slide toddler razor book happy fancy gospel tennis maple dilemma loan word shrug inflict delay length", "0x68a79eaca2324873eacc50cb9c6eca8cc68ea5d936f98787c60c7ebc74e6ce7c", "0x7c60c555126c297deddddd59f8cdcdc9e3608944455824dd604897984b5cc369cad749803bb36eb8b786b570c9cdc8db275dbe841486676a6adf389f3be3f076" },
   MnemonicSeedAndMiniSecretTestParams{ "scheme spot photo card baby mountain device kick cradle pact join borrow", "0xc0ba5a8e914111210f2bd131f3d5e08d", "0xc12157bf2506526c4bd1b79a056453b071361538e9e2c19c28ba2cfa39b5f23034b974e0164a1e8acd30f5b4c4de7d424fdb52c0116bfc6a965ba8205e6cc121" },
   MnemonicSeedAndMiniSecretTestParams{ "horn tenant knee talent sponsor spell gate clip pulse soap slush warm silver nephew swap uncle crack brave", "0x6d9be1ee6ebd27a258115aad99b7317b9c8d28b6d76431c3", "0x23766723e970e6b79dec4d5e4fdd627fd27d1ee026eb898feb9f653af01ad22080c6f306d1061656d01c4fe9a14c05f991d2c7d8af8730780de4f94cd99bd819" },
   MnemonicSeedAndMiniSecretTestParams{ "panda eyebrow bullet gorilla call smoke muffin taste mesh discover soft ostrich alcohol speed nation flash devote level hobby quick inner drive ghost inside", "0x9f6a2878b2520799a44ef18bc7df394e7061a224d2c33cd015b157d746869863", "0xf4c83c86617cb014d35cd87d38b5ef1c5d5c3d58a73ab779114438a7b358f457e0462c92bddab5a406fe0e6b97c71905cf19f925f356bc673ceb0e49792f4340" },
   MnemonicSeedAndMiniSecretTestParams{ "cat swing flag economy stadium alone churn speed unique patch report train", "0x23db8160a31d3e0dca3688ed941adbf3", "0x719d4d4de0638a1705bf5237262458983da76933e718b2d64eb592c470f3c5d222e345cc795337bb3da393b94375ff4a56cfcd68d5ea25b577ee9384d35f4246" },
   MnemonicSeedAndMiniSecretTestParams{ "light rule cinnamon wrap drastic word pride squirrel upgrade then income fatal apart sustain crack supply proud access", "0x8197a4a47f0425faeaa69deebc05ca29c0a5b5cc76ceacc0", "0x7ae1291db32d16457c248567f2b101e62c5549d2a64cd2b7605d503ec876d58707a8d663641e99663bc4f6cc9746f4852e75e7e54de5bc1bd3c299c9a113409e" },
   MnemonicSeedAndMiniSecretTestParams{ "all hour make first leader extend hole alien behind guard gospel lava path output census museum junior mass reopen famous sing advance salt reform", "0x066dca1a2bb7e8a1db2832148ce9933eea0f3ac9548d793112d9a95c9407efad", "0xa911a5f4db0940b17ecb79c4dcf9392bf47dd18acaebdd4ef48799909ebb49672947cc15f4ef7e8ef47103a1a91a6732b821bda2c667e5b1d491c54788c69391" },
   MnemonicSeedAndMiniSecretTestParams{ "vessel ladder alter error federal sibling chat ability sun glass valve picture", "0xf30f8c1da665478f49b001d94c5fc452", "0x4e2314ca7d9eebac6fe5a05a5a8d3546bc891785414d82207ac987926380411e559c885190d641ff7e686ace8c57db6f6e4333c1081e3d88d7141a74cf339c8f" },
   MnemonicSeedAndMiniSecretTestParams{ "scissors invite lock maple supreme raw rapid void congress muscle digital elegant little brisk hair mango congress clump", "0xc10ec20dc3cd9f652c7fac2f1230f7a3c828389a14392f05", "0x7a83851102849edc5d2a3ca9d8044d0d4f00e5c4a292753ed3952e40808593251b0af1dd3c9ed9932d46e8608eb0b928216a6160bd4fc775a6e6fbd493d7c6b2" },
   MnemonicSeedAndMiniSecretTestParams{ "void come effort suffer camp survey warrior heavy shoot primary clutch crush open amazing screen patrol group space point ten exist slush involve unfold", "0xf585c11aec520db57dd353c69554b21a89b20fb0650966fa0a9d6f74fd989d8f", "0x938ba18c3f521f19bd4a399c8425b02c716844325b1a65106b9d1593fbafe5e0b85448f523f91c48e331995ff24ae406757cff47d11f240847352b348ff436ed" }
));
