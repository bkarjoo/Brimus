//
// Created by b.karjoo on 4/11/2017.
//

#ifndef BRIMUS_MS_ORDER_COLLECTION_CHECK_H
#define BRIMUS_MS_ORDER_COLLECTION_CHECK_H
#include "ms_order_collection.h"
#include "ms_order.h"
#include "gtest/gtest.h"
#include "stdafx.h"
using namespace std;
TEST(ms_order_colection_test, test1)
{
    ms_order_collection moc;

    auto order = make_unique<ms_order>(100,"SPY",125.23,"aksd;fkja;");
    moc.add_order(move(order));
    EXPECT_EQ(1, moc.size());

}

TEST(ms_order_colection_test, test2)
{
    ms_order_collection moc;

    auto order = make_unique<ms_order>(100,"SPY",125.23,"aksd;fkja;");
    moc.add_order(move(order));
    auto order2 = make_unique<ms_order>(100,"SPY",125.23,"adsd;fkja;");
    moc.add_order(move(order2));
    moc.remove_order("aksd;fkja;");
    EXPECT_EQ(1, moc.size());
    moc.remove_order("adsd;fkja;");
    EXPECT_EQ(0, moc.size());
}

#endif