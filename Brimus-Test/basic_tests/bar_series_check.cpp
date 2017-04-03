//
// Created by b.karjoo on 3/27/2017.
//
#include "gtest/gtest.h"
#include "bar_series.h"

TEST(bar_series_check, test_eq) {
    EXPECT_EQ(1,1);
}

TEST(bar_series_check, test_eq2) {
EXPECT_NE(1,0);
}

TEST(bar_series_check, TestName) {
    EXPECT_EQ(1,1);
}


TEST(bar_series_check, AverageClose) {
    bar_series bs("MOCK");
    bs.add_price("93031000", 35.23);
    bs.add_price("93031000", 36.23);
    bs.add_price("93031000", 34.23);
    bs.add_price("93031000", 35.83);
    bs.add_price("93131000", 34.23);
    bs.add_price("93131000", 34.63);
    bs.add_price("93131000", 36.23);
    bs.add_price("93131000", 35.33);
    bs.add_price("93231000", 33.12);
    bs.add_price("93231000", 34.22);
    bs.add_price("93231000", 35.32);
    bs.add_price("93231000", 36.48);
    EXPECT_DOUBLE_EQ(35.83,bs.PreviousBar(2)->get_close());
    EXPECT_DOUBLE_EQ(35.33,bs.PreviousBar(1)->get_close());
    EXPECT_DOUBLE_EQ(36.48,bs.CurrentBar()->get_close());
    EXPECT_DOUBLE_EQ(35.88,bs.AverageClose(3));
    EXPECT_DOUBLE_EQ(35.58,bs.AverageClose(2,1));
    EXPECT_DOUBLE_EQ(36.23,bs.PreviousBar(2)->get_high());
    EXPECT_DOUBLE_EQ(36.23,bs.PreviousBar(1)->get_high());
    EXPECT_DOUBLE_EQ(36.48,bs.CurrentBar()->get_high());
    EXPECT_DOUBLE_EQ(36.313333333333333,bs.AverageHigh(3));
    EXPECT_DOUBLE_EQ(36.23,bs.AverageHigh(2,1));
    EXPECT_DOUBLE_EQ(34.23,bs.PreviousBar(2)->get_low());
    EXPECT_DOUBLE_EQ(34.23,bs.PreviousBar(1)->get_low());
    EXPECT_DOUBLE_EQ(33.12,bs.CurrentBar()->get_low());
    EXPECT_DOUBLE_EQ(33.86,bs.AverageLow(3));
    EXPECT_DOUBLE_EQ(34.23,bs.AverageLow(2,1));
    EXPECT_DOUBLE_EQ(36.48,bs.MaxClose(3));
    EXPECT_DOUBLE_EQ(35.33,bs.MinClose(3));
    EXPECT_DOUBLE_EQ(35.83,bs.MaxClose(2,1));
    EXPECT_DOUBLE_EQ(35.33,bs.MinClose(2,1));
    EXPECT_DOUBLE_EQ(36.48,bs.MaxHigh(3));
    EXPECT_DOUBLE_EQ(36.23,bs.MinHigh(3));
    EXPECT_DOUBLE_EQ(36.23,bs.MaxHigh(2,1));
    EXPECT_DOUBLE_EQ(36.23,bs.MinHigh(2,1));
    EXPECT_DOUBLE_EQ(34.23,bs.MaxLow(3));
    EXPECT_DOUBLE_EQ(33.12,bs.MinLow(3));
    EXPECT_DOUBLE_EQ(34.23,bs.MaxLow(2,1));
    EXPECT_DOUBLE_EQ(34.23,bs.MinLow(2,1));

}
