//
// Created by b.karjoo on 4/11/2017.
//
#include <global_basket.h>
#include "gtest/gtest.h"
#include "stdafx.h"
#include "market_simulator.h"
#include "instrument.h"
#include "st_message.h"
#include "st_field.h"

using namespace std;

TEST(market_simulator_tests, ping)
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


    auto response = ms.ping("SPY");
    auto response2 = ms.ping();
    EXPECT_EQ("129.320000", response);
    EXPECT_EQ("Connected.", response2);
}

TEST(market_simulator_tests, add_instrument)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    st_message m;
    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }


    EXPECT_EQ("129.320000",ms.ping("AAPL"));
}

TEST(market_simulator_tests, send_order)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    st_message m;
    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }



    EXPECT_EQ("129.320000",ms.ping("AAPL"));

    string id = ms.send_order(100, "AAPL", 129.33);

    EXPECT_TRUE(id.length() > 0);

    EXPECT_EQ(0, ms.open_orders_size());
    EXPECT_EQ(1, ms.closed_orders_size());
}

TEST(market_simulator_tests, cancel_order)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    st_message m;
    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }



    EXPECT_EQ("129.320000",ms.ping("AAPL"));

    string id = ms.send_order(100,"AAPL", 129);

    EXPECT_EQ(1, ms.open_orders_size());

    ms.cancel_order(id);

    EXPECT_EQ(0, ms.open_orders_size());

    id = ms.send_order(-100,"AAPL", 229);

    EXPECT_EQ(1, ms.open_orders_size());

    ms.cancel_order(id);

    EXPECT_EQ(0, ms.open_orders_size());
}

TEST(market_simulator_tests, cancel_replace_order)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    st_message m;
    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }



    EXPECT_EQ("129.320000",ms.ping("AAPL"));

    string id = ms.send_order(100,"AAPL", 129);

    EXPECT_EQ(1, ms.open_orders_size());

    id = ms.cancel_replace_order(id, 129.1);

    EXPECT_EQ(1, ms.open_orders_size());

    id = ms.cancel_replace_order(id, 200.1);

    EXPECT_EQ(0, ms.open_orders_size());

    id = ms.send_order(-100,"AAPL", 229);

    EXPECT_EQ(1, ms.open_orders_size());

    ms.cancel_replace_order(id,120);

    EXPECT_EQ(0, ms.open_orders_size());
}

TEST(market_simulator_tests, cancel_replace_order_shares)
{
    global_basket& gb = global_basket::get_instance();
    market_simulator& ms = market_simulator::get_instance();
    auto& inst = gb.add_instrument("AAPL");
    st_message m;
    // last
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.32";
        char a = 't', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // bid
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.31";
        char a = 'b', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }
    // ask
    {
        auto msg = make_unique<st_message>();
        st_field f;
        std::string s = "AAPL", s2 = "", s3 = "129.33";
        char a = 'a', b = 0;
        msg->set_symbol(s);
        msg->add_field(a, s2, s3, b);
        inst.on_message(move(msg));
    }



    EXPECT_EQ("129.320000",ms.ping("AAPL"));

    string id = ms.send_order(100,"AAPL", 129);

    EXPECT_EQ(1, ms.open_orders_size());

    id = ms.cancel_replace_order(id, 129.1);

    EXPECT_EQ(1, ms.open_orders_size());

    id = ms.cancel_replace_order(id, 200.1);

    EXPECT_EQ(0, ms.open_orders_size());

    id = ms.send_order(-100,"AAPL", 229);

    EXPECT_EQ(1, ms.open_orders_size());

    ms.cancel_replace_order(id,120);


    EXPECT_EQ(0, ms.open_orders_size());
}

TEST(market_simulator_tests, notify)
{

}

