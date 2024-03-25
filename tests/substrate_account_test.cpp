#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct AccountTestParams
{
   substrate::Account account;
   std::string public_key;
   std::string address;
};

class AccountTest : public testing::TestWithParam<AccountTestParams>
{
};

TEST_P(AccountTest, is_account_correct)
{
   auto params = GetParam();
   EXPECT_EQ(params.account->get_public_key(), substrate::hex_decode(params.public_key));
   EXPECT_EQ(params.account->get_address(), params.address);
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, AccountTest, testing::Values(
   AccountTestParams{ substrate::development::make_account_alice(), "0xd43593c715fdd31c61141abd04a99fd6822c8558854ccde39a5684e7a56da27d", "5GrwvaEF5zXb26Fz9rcQpDWS57CtERHpNehXCPcNoHGKutQY" },
   AccountTestParams{ substrate::development::make_account_bob(), "0x8eaf04151687736326c9fea17e25fc5287613693c912909cb226aa4794f26a48", "5FHneW46xGXgs5mUiveU4sbTyGBzmstUspZC92UhjJM694ty" }
));
