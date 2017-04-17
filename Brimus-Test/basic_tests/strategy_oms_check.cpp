//
// Created by b.karjoo on 3/29/2017.
//
#include <global_basket.h>
#include "gtest/gtest.h"
#include "strategy_oms.h"
#include "market_simulator.h"
#include "st_message.h"
#include "st_field.h"
#include "stdafx.h"
#include "global_basket.h"

using namespace std;


TEST(strategy_oms_tests, test1) {
    strategy_oms oms;
    //oms.submit(100,"SPY",124);

    EXPECT_EQ(1,1);
}

/*
 * strategy oms sends orders to market_simulator
 * therefore both need to be used here
 */
TEST(strategy_oms_tests, send_order)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("SPY");

    st_message m;

    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "SPY", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "SPY", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "SPY", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }

    strategy_oms oms;
    string id = oms.submit(100,"SPY",132);
    EXPECT_TRUE(id.length() > 0);
    EXPECT_EQ(1, ms.closed_orders_size());
}