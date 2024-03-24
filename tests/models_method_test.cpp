#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct MethodTestParams
{
   std::string Hex;
   uint8_t ModuleIndex{0};
   uint8_t CallIndex{0};
   std::vector<uint8_t> Parameters{};
};

class MethodTest : public testing::TestWithParam<MethodTestParams>
{
};

TEST_P(MethodTest, Encode)
{
   auto params = GetParam();
   const substrate::models::Method method{params.ModuleIndex, params.CallIndex, params.Parameters};

   substrate::encoder encoder;
   encoder << method;
   EXPECT_EQ(encoder.assemble_hex(), params.Hex);
}

TEST_P(MethodTest, Decode)
{
   auto params = GetParam();
   substrate::decoder decoder(substrate::hex_decode(params.Hex));
   substrate::models::Method method;
   decoder >> method;

   EXPECT_EQ(method.ModuleIndex, params.ModuleIndex);
   EXPECT_EQ(method.CallIndex, params.CallIndex);
   EXPECT_EQ(method.Parameters, params.Parameters);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, MethodTest, testing::Values(
   MethodTestParams{"0x0602", 0x06, 0x02, std::vector<uint8_t>{}},
   MethodTestParams{"0x06000100000000000000", 0x06, 0x00, std::vector<uint8_t>{0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
));