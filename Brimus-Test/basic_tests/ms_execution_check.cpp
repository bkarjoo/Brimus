//
// Created by b.karjoo on 4/12/2017.
//
#include "gtest/gtest.h"
#include "ms_execution.h"

TEST(ms_execution_tests, construction) {
    ms_execution me(100,"SPY",25.34);
    EXPECT_EQ(100,me.getQuantity());
    EXPECT_EQ("SPY",me.getSymbol());
    EXPECT_DOUBLE_EQ(25.34,me.getPrice());
}
