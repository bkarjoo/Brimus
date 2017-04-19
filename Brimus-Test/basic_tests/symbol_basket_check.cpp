//
// Created by b.karjoo on 3/30/2017.
//
#include "gtest/gtest.h"
#include "strategy_symbol_basket.h"

TEST(symbol_basket_tests, test1)
{
    strategy_symbol_basket sb;
    sb.add_symbol("AAPL");
    sb.add_symbol("AAPL");
    int count = sb.get_symbol_count();
    EXPECT_EQ(1, count);
}


