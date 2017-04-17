//
// Created by b.karjoo on 4/12/2017.
//
#include "gtest/gtest.h"
#include "execution.h"

TEST(execution_tests, contruction)
{
    execution e(100, "WPY", 127.2, "12312");
    EXPECT_EQ("WPY", e.getSymbol());
}

TEST(execution_tests, id)
{
    execution e(100, "WPY", 127.2, "12312");
    e.setId("Hello");
    EXPECT_EQ("Hello", e.getId());
}

TEST(execution_tests, qty)
{
    execution e(100, "WPY", 127.2, "12312");
    e.setQuantity(200);
    EXPECT_EQ(200, e.getQuantity());
}

TEST(execution_tests, price)
{
    execution e(100, "WPY", 127.2, "12312");
    e.setPrice(200.32);
    EXPECT_DOUBLE_EQ(200.32, e.getPrice());
}

TEST(execution_test, money_flow)
{
    execution e(100, "WPY", 127.2, "12312");
    // money flow is negative because you paid to buy
    EXPECT_DOUBLE_EQ(-12720, e.money_flow());
}
