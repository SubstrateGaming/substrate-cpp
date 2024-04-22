#include <gtest/gtest.h>

#include <substrate/hash.h>
#include <substrate/hex.h>

struct HashTestParams
{
   std::string Expected;
   std::vector<uint8_t> Bytes;
};

class HashTestBlake2 : public testing::TestWithParam<HashTestParams>
{
};

class HashTestSHA256 : public testing::TestWithParam<HashTestParams>
{
};

class HashTestSHA512 : public testing::TestWithParam<HashTestParams>
{
};

TEST_P(HashTestBlake2, Hash)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::hash::blake2(params.Bytes), substrate::hex_decode(params.Expected));
}

TEST_P(HashTestSHA256, Hash)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::hash::sha256(params.Bytes), substrate::hex_decode(params.Expected));
}

TEST_P(HashTestSHA512, Hash)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::hash::sha512(params.Bytes), substrate::hex_decode(params.Expected));
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, HashTestBlake2, testing::Values(
   HashTestParams{"0xd6bfa4fbbbb302d0f4e13a8904673181", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x01}},
   HashTestParams{"0x27c35e6e9373877f29e562464e46497e", std::vector<uint8_t>{0x61}},
   HashTestParams{"0xbd21ffc6c919770b9b19389c3deb819e", std::vector<uint8_t>{0x62, 0x62, 0x62}},
   HashTestParams{"0x815f32ac698e44efe27b338a1f16ddb1", std::vector<uint8_t>{0x63, 0x63, 0x63}},
   HashTestParams{"0x834061332e32438e7525a4a594949a5c", std::vector<uint8_t>{0x73, 0x69, 0x6d, 0x70, 0x6c, 0x79, 0x20, 0x61, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67}},
   HashTestParams{"0x5e7205b7d130f2260d0de6af473fa77f", std::vector<uint8_t>{0x00, 0xeb, 0x15, 0x23, 0x1d, 0xfc, 0xeb, 0x60, 0x92, 0x58, 0x86, 0xb6, 0x7d, 0x06, 0x52, 0x99, 0x92, 0x59, 0x15, 0xae, 0xb1, 0x72, 0xc0, 0x66, 0x47}},
   HashTestParams{"0xa467d541bcfc655a8bf9f2cb53968d36", std::vector<uint8_t>{0x51, 0x6b, 0x6f, 0xcd, 0x0f}},
   HashTestParams{"0x798bb8687e807ffe86f76f364f479bf5", std::vector<uint8_t>{0xbf, 0x4f, 0x89, 0x00, 0x1e, 0x67, 0x02, 0x74, 0xdd}},
   HashTestParams{"0xb64eee199750cacebf324edd4553ce15", std::vector<uint8_t>{0x57, 0x2e, 0x47, 0x94}},
   HashTestParams{"0x68826c52f3a59365d0f6fda7b5bd8123", std::vector<uint8_t>{0xec, 0xac, 0x89, 0xca, 0xd9, 0x39, 0x23, 0xc0, 0x23, 0x21}},
   HashTestParams{"0x2eac74f5e4f1e16b7f4514c962200336", std::vector<uint8_t>{0x10, 0xc8, 0x51, 0x1e}},
   HashTestParams{"0xd8137e27c3ff130fd78d6c2e29a9fa1b", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
));

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, HashTestSHA256, testing::Values(
   HashTestParams{"0xb40711a88c7039756fb8a73827eabe2c0fe5a0346ca7e0a104adc0fc764f528d", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x01}},
   HashTestParams{"0xca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb", std::vector<uint8_t>{0x61}},
   HashTestParams{"0x3e744b9dc39389baf0c5a0660589b8402f3dbb49b89b3e75f2c9355852a3c677", std::vector<uint8_t>{0x62, 0x62, 0x62}},
   HashTestParams{"0x64daa44ad493ff28a96effab6e77f1732a3d97d83241581b37dbd70a7a4900fe", std::vector<uint8_t>{0x63, 0x63, 0x63}},
   HashTestParams{"0xf54ff2ed083aa63a1be6f72e3232f18d6f34f49546ff20645dd7af1e65372a4c", std::vector<uint8_t>{0x73, 0x69, 0x6d, 0x70, 0x6c, 0x79, 0x20, 0x61, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67}},
   HashTestParams{"0x21d07b7aa2b72889abe01d1304fa2673b2ca1fcc75c9ed1c678d5148e72e0e23", std::vector<uint8_t>{0x00, 0xeb, 0x15, 0x23, 0x1d, 0xfc, 0xeb, 0x60, 0x92, 0x58, 0x86, 0xb6, 0x7d, 0x06, 0x52, 0x99, 0x92, 0x59, 0x15, 0xae, 0xb1, 0x72, 0xc0, 0x66, 0x47}},
   HashTestParams{"0xf4da40d6abdf27a5550d9c3198d1c0720ef1b115725d9204cf57990ec0860548", std::vector<uint8_t>{0x51, 0x6b, 0x6f, 0xcd, 0x0f}},
   HashTestParams{"0x04c4d7741b0e459e04ee49cc059cfec15e7c724b841c37bb9f2609f3abc1dc6f", std::vector<uint8_t>{0xbf, 0x4f, 0x89, 0x00, 0x1e, 0x67, 0x02, 0x74, 0xdd}},
   HashTestParams{"0x2e157c1b7b359f9e3cb1556044df5cb15b7eff05ef3d9d40f298cb008dc9a2e9", std::vector<uint8_t>{0x57, 0x2e, 0x47, 0x94}},
   HashTestParams{"0x154be9d7297f8ff49c623cb33ebccafdf3c4acb9f5d2139fd5989657a054f215", std::vector<uint8_t>{0xec, 0xac, 0x89, 0xca, 0xd9, 0x39, 0x23, 0xc0, 0x23, 0x21}},
   HashTestParams{"0xe372f90f5106d70b13de17148b6556f51211d8e3927eebb4e11d986c6312fc3a", std::vector<uint8_t>{0x10, 0xc8, 0x51, 0x1e}},
   HashTestParams{"0x01d448afd928065458cf670b60f5a594d735af0172c8d67f22a81680132681ca", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
));

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, HashTestSHA512, testing::Values(
   HashTestParams{"0x57c365278e08f99674dd24f08425b17c71b0511dea3b5ffa474deeb26d64cb993ebda4650583b29cba6307d7f4dbb42ca11b093de2b8ecab16ff52445401facf", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x01}},
   HashTestParams{"0x1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75", std::vector<uint8_t>{0x61}},
   HashTestParams{"0x5edc1c6a4390075a3ca27f4d4161c46b374b1c3b2d63f846db6fff0c513203c3ac3b14a24a6f09d8bf21407a4842113b5d9aa359d266299c3d6cf9e92db66dbe", std::vector<uint8_t>{0x62, 0x62, 0x62}},
   HashTestParams{"0x2b83283b8caf7e952ad6b0443a87cd9ee263bc32c4d78c5b678ac03556175059679b4b8513b021b16a27f6d2a35484703129129f35b6cdfe418ef6473b1f8f23", std::vector<uint8_t>{0x63, 0x63, 0x63}},
   HashTestParams{"0x47dd988f50a4817545f86e82d3b7e33ef6696d08567464cb3190827b95ffc6e7d9f4eeff0008501bccf3f3e2bfb524f1388065ae6d3cdc1cf4bbf3ebe06b053a", std::vector<uint8_t>{0x73, 0x69, 0x6d, 0x70, 0x6c, 0x79, 0x20, 0x61, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67}},
   HashTestParams{"0xc6b7ad0cc279981881b6ed0036a8ff63c1ddc837b316a61a80c40149ded1f4316a7e9b404ca64e1ff0685b59333e9a710c4a3abd19a1750ad25521537be4383a", std::vector<uint8_t>{0x00, 0xeb, 0x15, 0x23, 0x1d, 0xfc, 0xeb, 0x60, 0x92, 0x58, 0x86, 0xb6, 0x7d, 0x06, 0x52, 0x99, 0x92, 0x59, 0x15, 0xae, 0xb1, 0x72, 0xc0, 0x66, 0x47}},
   HashTestParams{"0xa102a7f4f5a712296983706aed3f27650a3cedc8b3105475ce88f6b06586f40f42bfbba8fcfbcb0be11d87b01449fcf9cb65485a16fd857db97a82dc91aec8ab", std::vector<uint8_t>{0x51, 0x6b, 0x6f, 0xcd, 0x0f}},
   HashTestParams{"0x45dcd93dc1534c00b8b2f96b1842902f71d65ddcea70f15446935c803fd14f8b3b7f2d647aca28d1124745db98f2a2680fd482e3a5da7a9e5aa9d883f5089a8d", std::vector<uint8_t>{0xbf, 0x4f, 0x89, 0x00, 0x1e, 0x67, 0x02, 0x74, 0xdd}},
   HashTestParams{"0x8bf61264601b3d0941f2238bc15cc00b73a4cc1de1e1569e984be1a992853abe974cc0429a06b184873e4d3929fc825adfe2f606e4fd4ff6d4382bccaea23b8f", std::vector<uint8_t>{0x57, 0x2e, 0x47, 0x94}},
   HashTestParams{"0x5cdb0398321b513fb961b19adc25acd371778bd3923a6ca6c5b07cb4055ecde73c82577308f5fd28230c866fe861ecc599ec1caad2b40191124d460c3a2e46e9", std::vector<uint8_t>{0xec, 0xac, 0x89, 0xca, 0xd9, 0x39, 0x23, 0xc0, 0x23, 0x21}},
   HashTestParams{"0x213f3986ce52032a72eeef7e1d734935e63e26d831b6bee0777862a022c08c89174405e0ee368d171fd3cc59296fec6d8228d0415d68a88d81115bfce3e3d55f", std::vector<uint8_t>{0x10, 0xc8, 0x51, 0x1e}},
   HashTestParams{"0x19bd3cbb62b1937957a11cabd0d39860582b6928e77d0e0ea5ee7f3b2f8cacb3dea8ea0972651adc3245fd10926f2f31e80377196e4e6c7ee2bd74051e58bcba", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
));
