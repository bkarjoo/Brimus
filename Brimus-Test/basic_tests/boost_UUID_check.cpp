//
// Created by b.karjoo on 4/11/2017.
//
#include "gtest/gtest.h"
#include "stdafx.h"

using namespace std;
TEST(boost_UUID_tests, test1)
{
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid1 = generator();
    string id =  boost::lexical_cast<string>(uuid1);
    EXPECT_TRUE(id.length() > 0);
}
