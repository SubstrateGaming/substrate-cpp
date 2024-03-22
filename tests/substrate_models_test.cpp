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
   substrate::models::Era era;
   era.Period = params.Period;
   era.Phase = params.Phase;

   substrate::encoder encoder;
   encoder << era;
   EXPECT_EQ(encoder.assemble(), params.Expected);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, EraTest, testing::Values(
   EraTestParams{2048, 99, {58, 6}},
   EraTestParams{64, 52, {69, 3}},
   EraTestParams{64, 47, {245, 2}}
));
