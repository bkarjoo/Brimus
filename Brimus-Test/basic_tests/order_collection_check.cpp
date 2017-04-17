//
// Created by b.karjoo on 4/7/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "order_collection.h"
#include "order.h"
using namespace std;
TEST(order_collection_tests, test1) {
    order_collection oc;
    oc.add_order(100,"SPY",213.20);
    auto it = oc.find_order(100,"SPY",213.2);
    EXPECT_EQ(1,oc.size());
    EXPECT_EQ(it->getQuantity(),100);
}

TEST(order_collection_tests, add_order) {
    order_collection oc;
    oc.add_order(100,"SPY",213.20);
    EXPECT_EQ(1,oc.size());
}

TEST(order_collection_tests, remove_order) {
    order_collection oc;
    oc.add_order(100,"SPY",213.20);
    EXPECT_EQ(1,oc.size());
    oc.remove_order(100,"SPY",213.2);
    EXPECT_EQ(0,oc.size());
    auto it2 = oc.find_order(100,"SPY",213.2);
    EXPECT_FALSE(it2);
}

TEST(order_collection_tests, test4) {
    order_collection oc;
    oc.add_order(100,"SPY",213.20);
    EXPECT_TRUE(oc.has_open_buy_order("SPY"));
    oc.remove_order(100,"SPY",213.2);
    EXPECT_FALSE(oc.has_open_buy_order("SPY"));
}

TEST(order_collection_tests, test5)
{
    order_collection oc1;
    order_collection oc2;
    oc1.add_order(100,"SPY",213.20);
    EXPECT_EQ(1,oc1.size());
    EXPECT_EQ(0,oc2.size());
    oc2.pass_order(oc1.fetch_remove_order(100,"SPY",213.20));
    EXPECT_EQ(0,oc1.size());
    EXPECT_EQ(1,oc2.size());
}

TEST(order_collection_tests, find_boost_order)
{
    auto o = make_unique<order>(100,"SPY",32.10);
    o->setId("blah blah blah");

    order_collection oc;
    oc.pass_order(move(o));

    auto opt = oc.boost_find_order("blah blah blah");
    if(!opt) return;
    order & ord = *opt;
    EXPECT_EQ(100,ord.getQuantity());
}

TEST(order_collection_tests, find_raw_order)
{
    auto o = make_unique<order>(100,"SPY",32.10);
    o->setId("blah blah blah");

    order_collection oc;
    oc.pass_order(move(o));

    auto opt = oc.findOrder("blah blah blah");
    if(!opt) return;
    order & ord = *opt;
    EXPECT_EQ(100,ord.getQuantity());
}

//const ord_ptr& add_order(int qty, std::string symbol, double price);
//void pass_order(ord_ptr);
//const ord_ptr & find_order(std::string);
//const ord_ptr & find_order(int qty, std::string symbol, double price);
//void remove_order(int qty, std::string symbol, double price);
//ord_ptr fetch_remove_order(int qty, std::string symbol, double price);
//ord_ptr fetch_remove_order(std::string id);
//bool has_open_order(const std::string&) const;
//bool has_open_buy_order(const std::string&) const;
//bool has_open_sell_order(const std::string&) const;
//int size() const { return orders.size(); }