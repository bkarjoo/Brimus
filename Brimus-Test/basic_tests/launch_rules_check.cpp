//
// Created by b.karjoo on 3/30/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "launch_rules.h"
#include "holidays.h"

TEST(launch_rules_tests, add_date)
{
    launch_rules lr;
    lr.add_date(2015,1,1);

    EXPECT_EQ("2015-1-1",lr.to_string());
    lr.add_date(2015,1,2);
    EXPECT_EQ("2015-1-1\n2015-1-2",lr.to_string());
}

TEST(launch_rules_tests, test2)
{
    launch_rules lr;
    lr.setStartDate(2015,1,1);
    std::stringstream ss;
    ss << *lr.getStartDate();
    EXPECT_EQ("2015-Jan-01",ss.str());
    lr.setEndDate(2015,1,7);
    std::stringstream ss2;
    ss2 << *lr.getEndDate();
    EXPECT_EQ("2015-Jan-07",ss2.str());

    lr.set_date_range();
    EXPECT_EQ("2015-1-2\n2015-1-5\n2015-1-6\n2015-1-7", lr.to_string());
}

TEST(launch_rules_tests, loadHolidaysFromFile)
{
    holidays& h = holidays::get_instance();
    auto& a = h.getHolidays();
    launch_rules lr;
    boost::gregorian::date date1(2015,1,1);
    EXPECT_TRUE(a.size() > 0);
    EXPECT_TRUE(lr.is_holiday(date1));
    boost::gregorian::date date2(2015,1,2);
    EXPECT_FALSE(lr.is_holiday(date2));
}




