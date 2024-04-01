#pragma once
#include <gtest/gtest.h>
#include <substrate/substrate.h>

#include <thread>

class rpc_test : public ::testing::Test
{
   std::thread _event_loop;

protected:
   substrate::rpc::Client client;

   virtual void SetUp() override;
   virtual void TearDown() override;

private:
   void on_event_loop();
};
