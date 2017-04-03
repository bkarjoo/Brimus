//
// Created by b.karjoo on 3/31/2017.
//
#include "gtest/gtest.h"
#include <boost/date_time/gregorian/gregorian.hpp>

TEST(BoostDateTest, test1)
{
    boost::gregorian::date d1(2015,boost::gregorian::Jan,1);
    boost::gregorian::date d2(2015,boost::gregorian::Jan,2);
    std::stringstream ss;
    ss << d1.month().as_number();
    EXPECT_EQ("1", ss.str());
    EXPECT_TRUE(d1 < d2);
}

TEST(BoostDateTest, DayOfWeek)
{
    boost::gregorian::date d1(2015,boost::gregorian::Jan,1);
    boost::gregorian::date d2(2015,boost::gregorian::Jan,2);
    std::stringstream ss;
    ss << d1.day_of_week();
    EXPECT_EQ("Thu", ss.str());
    EXPECT_TRUE(d1.day_of_week() == boost::gregorian::Thursday);
}