//
// Created by b.karjoo on 4/10/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "execution_collection.h"
#include "execution.h"


using namespace std;

TEST(execution_collection_tests, add_unique_ptr)
{
    execution_collection ec;
    unique_ptr<execution> e = make_unique<execution>(100,"SPY",220.12);
    ec.add_execution(move(e));
    EXPECT_EQ(1, ec.execution_collection_size());
}

TEST(execution_collection_tests, add_raw_execution)
{
    execution_collection ec;
    ec.add_execution(100,"SPY",220.12);
    EXPECT_EQ(1, ec.execution_collection_size());
}

TEST(execution_collections_tests, find_last_fill)
{
    execution_collection ec;
    ec.add_execution(100,"SPY",220.12);
    ec.add_execution(100,"AAPL",127.34);
    ec.add_execution(100,"SPY",220.32);
    EXPECT_DOUBLE_EQ(220.32,ec.last_fill_price("SPY"));
}

TEST(execution_collections_tests, find_last_buy)
{
    execution_collection ec;
    ec.add_execution(100,"SPY",220.12);
    ec.add_execution(100,"AAPL",127.34);
    ec.add_execution(100,"SPY",220.32);
    EXPECT_DOUBLE_EQ(220.32,ec.last_buy_fill_price("SPY"));
}

TEST(execution_collections_tests, find_last_sell)
{
    execution_collection ec;
    ec.add_execution(-100,"SPY",220.14);
    ec.add_execution(100,"SPY",220.12);
    ec.add_execution(-100,"AAPL",127.34);
    ec.add_execution(-100,"SPY",220.34);
    EXPECT_DOUBLE_EQ(220.34,ec.last_sell_fill_price("SPY"));
}

TEST(execution_collections_tests, money_flow_test)
{
    execution_collection ec;
    ec.add_execution(-100,"SPY",220.22);
    ec.add_execution(100,"SPY",220.12);
    ec.add_execution(100,"AAPL",127.34);
    ec.add_execution(-100,"AAPL",127.44);
    EXPECT_TRUE(20-ec.sum_money_flow()<.0000001);
}