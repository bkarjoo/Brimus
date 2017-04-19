//
// Created by b.karjoo on 4/12/2017.
//
#include "gtest/gtest.h"
#include "ms_order.h"

TEST(ms_order_tests, getters) {
    ms_order order1(100,"SPY",222.22,"asdf-24ta-as4w2");
    EXPECT_DOUBLE_EQ(222.22, order1.getPrice());
    EXPECT_EQ("asdf-24ta-as4w2", order1.getId());
    EXPECT_EQ(100,order1.getQuantity());
    EXPECT_EQ("SPY",order1.getSymbol());
}

TEST(ms_order_tests, executions) {
    ms_order order1(1000,"SPY",222.22,"asdf-24ta-as4w2");
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    EXPECT_FALSE(order1.is_filled());
    EXPECT_EQ(400,order1.execution_qty());
    EXPECT_EQ(600, order1.remain_qty());
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    order1.add_execution(100,222.21);
    EXPECT_TRUE(order1.is_filled());
    EXPECT_EQ(1000,order1.execution_qty());
}