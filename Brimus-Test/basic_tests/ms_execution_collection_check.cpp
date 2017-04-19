//
// Created by b.karjoo on 4/10/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "ms_execution_collection.h"
#include "ms_execution.h"


using namespace std;

TEST(ms_execution_collection_tests, add_unique_ptr)
{
    ms_execution_collection ec;
    unique_ptr<ms_execution> e = make_unique<ms_execution>(100,"SPY",220.12);
    ec.add_execution(move(e));
    int count = 0;
    for (auto i = ec.begin(); i != ec.end(); ++i) count++;
    EXPECT_EQ(1, count);
}

