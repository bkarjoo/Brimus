//
// Created by b.karjoo on 4/7/2017.
//
#include "gtest/gtest.h"
#include "position_collection.h"

TEST(position_collection_test, test1) {
    position_collection pc;
    pc.add_position("SPY",100);
    EXPECT_EQ(100,pc.get_position("SPY"));
}

TEST(position_collection_test, test2) {
    position_collection pc;
    pc.add_position("AAPL",10000);
    EXPECT_EQ(10000,pc.get_position("AAPL"));
}

TEST(position_collection_test, test3) {
    position_collection pc;
    pc.add_position("AAPL",10000);
    EXPECT_TRUE(pc.has_position("AAPL"));
}

