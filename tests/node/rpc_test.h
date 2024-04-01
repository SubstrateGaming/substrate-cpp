#pragma once
#include <gtest/gtest.h>
#include <substrate/substrate.h>

class rpc_test : public ::testing::Test
{
protected:
   substrate::rpc::Client client;

   void SetUp() override;
   void TearDown() override;
};
