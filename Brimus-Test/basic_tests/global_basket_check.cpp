//
// Created by b.karjoo on 3/30/2017.
//
#include "gtest/gtest.h"
#include "global_basket.h"
#include "stdafx.h"


using namespace std;

TEST(global_basket_tests, AddInstrument) {
    auto& gb = global_basket::get_instance();
    auto& instrument = gb.add_instrument("AAPL");
    EXPECT_EQ("AAPL", instrument.getSymbol());
}

TEST(global_basket_tests, UpdateInstrument) {
    auto& gb = global_basket::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    auto msg = make_unique<st_message>();
    st_field f;
    std::string s = "AAPL", s2 = "", s3 = "129.32";
    char a = 't', b = 0;
    msg->set_symbol(s);
    msg->add_field(a, s2, s3, b);
    inst.on_message(move(msg));
    EXPECT_DOUBLE_EQ(129.32,gb.LastPrice("AAPL"));
}