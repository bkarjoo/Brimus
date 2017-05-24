//
// Created by b.karjoo on 5/1/2017.
//
#include "gtest/gtest.h"
#include "stdafx.h"
#include "simple_bar.h"
#include "simple_bar_series_check.h"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost;

TEST(simple_bar_series_tests, test_add_to_bar) {
    using namespace boost::gregorian;
    using namespace boost::posix_time;
    date d(2000,Jan,20);
    ptime start(d);

    simple_bar b(start, 25.34);
    EXPECT_EQ(25.34, b.getClose());
    b.add_price(38.23);
    EXPECT_EQ(38.23, b.getClose());
    EXPECT_EQ(38.23, b.getHigh());
    EXPECT_EQ(25.34, b.getLow());
}

TEST(simple_bar_series_tests, test_add_to_barseries) {
    using namespace boost::gregorian;
    using namespace boost::posix_time;
    date d(2000,Jan,20);
    ptime start(d);

    time_duration td{0,5,0};
    simple_bar_series sbs(td);
    sbs.add_price(start,25.34);
    sbs.add_price(start,26.24);
    sbs.add_price(start,23.64);
    sbs.add_price(start,25.14);
    EXPECT_EQ(26.24,sbs.CurrentBar().getHigh());
    start += td;

    sbs.add_price(start,22.34);
    sbs.add_price(start,21.24);
    sbs.add_price(start,22.64);
    sbs.add_price(start,26.14);
    EXPECT_EQ(26.14,sbs.CurrentBar().getHigh());

}