//
// Created by b.karjoo on 3/30/2017.
//
#include "gtest/gtest.h"
#include "launch_rules.h"
#include <iostream>

TEST(launch_rules_tests, test1)
{
    launch_rules lr;
    lr.add_date(2015,1,1);

    EXPECT_EQ("2015-1-1",lr.to_string());
}
