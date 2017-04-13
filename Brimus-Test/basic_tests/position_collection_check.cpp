//
// Created by b.karjoo on 4/7/2017.
//
#include "gtest/gtest.h"
#include "position_collection.h"

TEST(position_collection_test, addPosition) {
    position_collection pc;
    pc.add_position("SPY",100);
    EXPECT_EQ(100,pc.get_position("SPY"));
    pc.add_position("AAPL",10000);

    EXPECT_EQ(10000,pc.get_position("AAPL"));
}

TEST(position_collection_test, hasPosition) {
    position_collection pc;
    pc.add_position("AAPL",10000);
    EXPECT_TRUE(pc.has_position("AAPL"));
}

TEST(position_collection_test, addAndSubtract) {
    position_collection pc;
    pc.add_position("AAPL",10000);
    pc.add_position("AAPL",-10000);
    EXPECT_EQ(0,pc.get_position("AAPL"));
}

TEST(position_collection_test, bought) {
    position_collection pc;
    pc.bought("AAPL", 10000);
    pc.bought("AAPL",-10000);
    EXPECT_EQ(20000,pc.get_position("AAPL"));
}

TEST(position_collection_test, sold) {
    position_collection pc;
    pc.sold("AAPL" ,10000);
    pc.sold("AAPL",-10000);
    EXPECT_EQ(-20000,pc.get_position("AAPL"));
}