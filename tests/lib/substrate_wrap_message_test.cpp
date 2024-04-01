#include <gtest/gtest.h>

#include <substrate/substrate.h>

struct WrapMessageTestParams
{
   std::string Message;
   bool IsWrapped;
};

class WrapMessageTest : public testing::TestWithParam<WrapMessageTestParams>
{
};

TEST_P(WrapMessageTest, is_wrapped_test)
{
   auto params = GetParam();
   EXPECT_EQ(substrate::wrap_message::is_wrapped(params.Message), params.IsWrapped);
}

TEST(WrapMessageTest, UnwrapMessage_ShouldBeWrapped)
{
   const std::string message = "test";
   const std::vector<uint8_t> message_wrapped{60, 66, 121, 116, 101, 115, 62, 116, 101, 115, 116, 60, 47, 66, 121, 116, 101, 115, 62};
   EXPECT_EQ(substrate::wrap_message::is_wrapped(message), false);
   EXPECT_EQ(substrate::wrap_message::wrap(message), message_wrapped);
}

TEST(WrapMessageTest, WrapMessage_ShouldBeUnwrap)
{
   const std::string message = "<Bytes>test</Bytes>";
   const std::vector<uint8_t> message_unwrapped{116, 101, 115, 116};
   EXPECT_EQ(substrate::wrap_message::is_wrapped(message), true);
   EXPECT_EQ(substrate::wrap_message::unwrap(message), message_unwrapped);
}

TEST(WrapMessageTest, MultipleWrapAndUnwrap_ShouldBeUntouched)
{
   const std::string message = "IAmAMessage";
   EXPECT_EQ(substrate::wrap_message::wrap(substrate::wrap_message::wrap(substrate::wrap_message::wrap(message))), substrate::wrap_message::wrap(message));
   EXPECT_EQ(substrate::wrap_message::unwrap(substrate::wrap_message::unwrap(substrate::wrap_message::unwrap(message))), substrate::wrap_message::unwrap(message));
}

INSTANTIATE_TEST_SUITE_P(libSubstrate_tests, WrapMessageTest, testing::Values(
   WrapMessageTestParams{"<Bytes>test</Bytes>", true},
   WrapMessageTestParams{"<Bytes><byte>AlmostInception</byte></Bytes>", true},
   WrapMessageTestParams{"IamNotWrapped", false},
   WrapMessageTestParams{"<Byte>almostwrapped</Bytes>", false},
   WrapMessageTestParams{"<bytes>casesentitive</bytes>", false}
));
