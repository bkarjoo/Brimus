//
// Created by b.karjoo on 4/11/2017.
//
#include <gtest/gtest.h>
#include <bar.h>
#include <bar_time.h>

TEST(bar_tests, constructors)
{
    bar b;
    b.add_tick(25.54);
    EXPECT_DOUBLE_EQ(25.54, b.High());
}

TEST(bar_tests, getStartTime)
{
    bar b;
    bar_time bt(9,30);
    b.setStartTime(bt);
    EXPECT_EQ("093000000",b.getStartTime().to_string());
}

TEST(bar_tests, range)
{
    bar b;
    b.add_tick(25);
    b.add_tick(26);
    EXPECT_DOUBLE_EQ(1,b.range());
}

TEST(bar_tests, addTick)
{
    bar b;
    b.add_tick(22);
    b.add_tick(23);
    b.add_tick(20);
    b.add_tick(21);
    EXPECT_DOUBLE_EQ(22, b.Open());
    EXPECT_DOUBLE_EQ(23, b.High());
    EXPECT_DOUBLE_EQ(20, b.Low());
    EXPECT_DOUBLE_EQ(21, b.Close());

}

TEST(bar_tests, operatorLessThan)
{
 bar b1, b2;
    b1.setStartTime(bar_time(9,31));
    b2.setStartTime(bar_time(9,30));
    EXPECT_TRUE(b2<b1);
    EXPECT_TRUE(b1>b2);
}

