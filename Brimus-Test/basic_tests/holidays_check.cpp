//
// Created by b.karjoo on 4/12/2017.
//
#include "gtest/gtest.h"
#include "holidays.h"

TEST(holiday_tests, construct) {
    holidays& h = holidays::get_instance();
    auto& dates = h.getHolidays();
    EXPECT_TRUE(dates.size()>0);
}

TEST(holiday_tests, check_include) {
    holidays& h = holidays::get_instance();
    auto& dates = h.getHolidays();
    boost::gregorian::date d(2015,boost::gregorian::Jan, 1);
    EXPECT_TRUE(dates.find(d) != dates.end());
}