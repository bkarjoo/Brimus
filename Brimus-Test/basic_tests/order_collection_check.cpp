//
// Created by b.karjoo on 4/7/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "order_collection.h"

TEST(order_collection_tests, test1) {
    order_collection oc;
    oc.add_order(std::make_shared<order>(100,"SPY",213.20));
    auto it = oc.find_order(100,"SPY",213.2);
    EXPECT_EQ(1,oc.size());
    EXPECT_EQ(it->getQuantity(),100);
}

TEST(order_collection_tests, test2) {
    order_collection oc;
    oc.add_order(std::make_shared<order>(100,"SPY",213.20));
    oc.remove_order(100,"SPY",213.2);
    EXPECT_EQ(0,oc.size());
}

TEST(order_collection_tests, test3) {
    order_collection oc;
    oc.add_order(std::make_shared<order>(100,"SPY",213.20));
    EXPECT_EQ(1,oc.size());
    oc.remove_order(100,"SPY",213.2);
    EXPECT_EQ(0,oc.size());
    auto it2 = oc.find_order(100,"SPY",213.2);
    EXPECT_EQ(nullptr,it2);
}

TEST(order_collection_tests, test4) {
    order_collection oc;
    oc.add_order(std::make_shared<order>(100,"SPY",213.20));
    EXPECT_TRUE(oc.has_open_buy_order("SPY"));
    oc.remove_order(100,"SPY",213.2);
    EXPECT_FALSE(oc.has_open_buy_order("SPY"));
}

TEST(order_collection_tests, test5)
{
    order_collection oc1;
    order_collection oc2;
    oc1.add_order(std::make_shared<order>(100,"SPY",213.20));
    EXPECT_EQ(1,oc1.size());
    EXPECT_EQ(0,oc2.size());
    oc2.add_order(oc1.fetch_remove_order(100,"SPY",213.20));
    EXPECT_EQ(0,oc1.size());
    EXPECT_EQ(1,oc2.size());
}

