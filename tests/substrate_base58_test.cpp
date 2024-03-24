#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct Base58TestParams
{
   std::string Input;
   std::vector<uint8_t> Bytes;
};

class Base58Test : public testing::TestWithParam<Base58TestParams>
{
};

TEST_P(Base58Test, Encode)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::base58_encode(params.Bytes), params.Input);
}

TEST_P(Base58Test, Decode)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::base58_decode(params.Input), params.Bytes);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, Base58Test, testing::Values(
   Base58TestParams{"1112", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x01}},
   Base58TestParams{"2g", std::vector<uint8_t>{0x61}},
   Base58TestParams{"a3gV", std::vector<uint8_t>{0x62, 0x62, 0x62}},
   Base58TestParams{"aPEr", std::vector<uint8_t>{0x63, 0x63, 0x63}},
   Base58TestParams{"2cFupjhnEsSn59qHXstmK2ffpLv2", std::vector<uint8_t>{0x73, 0x69, 0x6d, 0x70, 0x6c, 0x79, 0x20, 0x61, 0x20, 0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67}},
   Base58TestParams{"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L", std::vector<uint8_t>{0x00, 0xeb, 0x15, 0x23, 0x1d, 0xfc, 0xeb, 0x60, 0x92, 0x58, 0x86, 0xb6, 0x7d, 0x06, 0x52, 0x99, 0x92, 0x59, 0x15, 0xae, 0xb1, 0x72, 0xc0, 0x66, 0x47}},
   Base58TestParams{"ABnLTmg", std::vector<uint8_t>{0x51, 0x6b, 0x6f, 0xcd, 0x0f}},
   Base58TestParams{"3SEo3LWLoPntC", std::vector<uint8_t>{0xbf, 0x4f, 0x89, 0x00, 0x1e, 0x67, 0x02, 0x74, 0xdd}},
   Base58TestParams{"3EFU7m", std::vector<uint8_t>{0x57, 0x2e, 0x47, 0x94}},
   Base58TestParams{"EJDM8drfXA6uyA", std::vector<uint8_t>{0xec, 0xac, 0x89, 0xca, 0xd9, 0x39, 0x23, 0xc0, 0x23, 0x21}},
   Base58TestParams{"Rt5zm", std::vector<uint8_t>{0x10, 0xc8, 0x51, 0x1e}},
   Base58TestParams{"1111111111", std::vector<uint8_t>{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
));
