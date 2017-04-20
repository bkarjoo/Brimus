//
// Created by b.karjoo on 4/19/2017.
//
#include "gtest/gtest.h"
#include "stock_collection.h"
#include "stdafx.h"
using namespace std;
TEST(stock_collection_tests, add_stock) {
    stock_collection& sc = stock_collection::get_instance();
    sc.add_stock("IBM");
    EXPECT_EQ(1,sc.size());
}

TEST(stock_collection_tests, static_persistence) {
    stock_collection& sc = stock_collection::get_instance();
    EXPECT_EQ(1, sc.size());
}

TEST(stock_collection_tests, symbol_update) {
    stock_collection& sc = stock_collection::get_instance();
    auto s = sc.get_stock("IBM");
    cap_message sm;
    string* symb = new string("IBM");
    sm.set_symbol(*symb);
    cap_msg_field cmf;
    cmf.field_code = ('t');
    cmf.field_value = "125.12";
    sm.add_field(cmf.field_code,cmf.field_code_value,cmf.field_value, cmf.field_exchange);

    s->tick_update(sm);
    EXPECT_DOUBLE_EQ(125.12,s->Last());
}

TEST(stock_collection_tests, has_symbol) {
    stock_collection& sc = stock_collection::get_instance();
    EXPECT_EQ(1, sc.size());
    auto s = sc.get_stock("IBM");
    EXPECT_DOUBLE_EQ(125.12,s->Last());
    EXPECT_TRUE(sc.has_instrument("IBM"));
}




