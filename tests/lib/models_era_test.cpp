#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct EraTestParams
{
   uint64_t Period;
   uint64_t Phase;
   std::vector<uint8_t> Expected;
};

class EraTest : public testing::TestWithParam<EraTestParams>
{
};

TEST_P(EraTest, Encode)
{
   auto params = GetParam();
   substrate::rpc::Era era;
   era.Period = params.Period;
   era.Phase = params.Phase;

   substrate::encoder encoder;
   encoder << era;
   EXPECT_EQ(encoder.assemble(), params.Expected);
}

TEST_P(EraTest, Decode)
{
   auto params = GetParam();
   substrate::decoder decoder(params.Expected);
   substrate::rpc::Era era;
   decoder >> era;
   EXPECT_EQ(era.Period, params.Period);
   EXPECT_EQ(era.Phase, params.Phase);
}

TEST(EraTest, EraBeginTest)
{
   substrate::rpc::Era era{false, 64, 49};
   EXPECT_EQ(1585, era.get_start(1587));
}

TEST(EraTest, EraCreateTest)
{
   substrate::rpc::Era era = substrate::rpc::Era::make(12, 15686);
   EXPECT_EQ(era.Period, 16);
   EXPECT_EQ(era.Phase, 6);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, EraTest, testing::Values(
   EraTestParams{2048, 99, {0x3A, 0x06}},
   EraTestParams{64, 52, {0x45, 0x03}},
   EraTestParams{64, 47, {0xF5, 0x02}}
));
