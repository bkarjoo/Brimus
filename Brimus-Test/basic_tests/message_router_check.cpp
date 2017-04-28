//
// Created by b.karjoo on 4/27/2017.
//
#include "gtest/gtest.h"
#include "message_router.h"

TEST(message_router_tests, convert) {
    message_router mr;
    boost::posix_time::ptime x = mr.convert_time("00:08:34 01/03/2017");
    boost::posix_time::ptime t = mr.convert_time("00:08:34 01/03/2017");
    EXPECT_EQ(x,t);
}