#include <gtest/gtest.h>
#include <substrate/substrate.h>

constexpr uint16_t NET_KUSAMA = 2;
constexpr uint16_t NET_SUBSTRATE = 42;
constexpr uint16_t NET_AJUNA = 1328;
constexpr uint16_t NET_BAJUN = 1337;

const std::vector<uint8_t> PublicKeyForTestCase = {
   0xD4, 0x35, 0x93, 0xC7, 0x15, 0xFD, 0xD3, 0x1C,
   0x61, 0x14, 0x1A, 0xBD, 0x04, 0xA9, 0x9F, 0xD6,
   0x82, 0x2C, 0x85, 0x58, 0x85, 0x4C, 0xCD, 0xE3,
   0x9A, 0x56, 0x84, 0xE7, 0xA5, 0x6D, 0xA2, 0x7D
};

struct AddressPublicKeyTestParams
{
   std::string Address;
   uint16_t AddressNetwork;
   std::vector<uint8_t> AddressPublicKey;
};

class AddressPublicKeyTest : public testing::TestWithParam<AddressPublicKeyTestParams>
{
};

TEST_P(AddressPublicKeyTest, GetPublicKey)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::get_public_key(params.Address), params.AddressPublicKey);
}

TEST_P(AddressPublicKeyTest, GetPublicKeyAndNetwork)
{
   auto params = GetParam();
   uint16_t network = 0;
   EXPECT_EQ(substrate::get_public_key_with_network(params.Address, network), params.AddressPublicKey);
   EXPECT_EQ(network, params.AddressNetwork);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, AddressPublicKeyTest, testing::Values(
   AddressPublicKeyTestParams{"HNZata7iMYWmk5RvZRTiAsSDhV8366zq2YGb3tLH5Upf74F", NET_KUSAMA, PublicKeyForTestCase },
   AddressPublicKeyTestParams{"5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY", NET_SUBSTRATE, PublicKeyForTestCase },
   AddressPublicKeyTestParams{"aUuBHS3LZKnPuxyDJYhteYPwGWg932LjHPtbBQKQBA55F4B1T", NET_AJUNA, PublicKeyForTestCase },
   AddressPublicKeyTestParams{"bUNdEKVCnhNAZvnEWFNcL3T82nAWQduR63fgon1qbrba7AKfN", NET_BAJUN, PublicKeyForTestCase }
));
