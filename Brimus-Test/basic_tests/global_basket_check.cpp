//
// Created by b.karjoo on 3/30/2017.
//
#include "gtest/gtest.h"
#include "global_basket.h"




TEST(global_basket_tests, AddInstrument) {
    auto& gb = global_basket::get_instance();
    auto was_added = gb.add_instrument("AAPL");
    EXPECT_TRUE(was_added != nullptr);
}

TEST(global_basket_tests, SubscribeToPCapFileUpdates) {
    auto& gb = global_basket::get_instance();
    gb.add_instrument("AAPL");
    // send a mock message to gb (mock file with one message)
    // get notified
    // check if the update happened

}