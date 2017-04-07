//
// Created by b.karjoo on 4/7/2017.
//
#include "gtest/gtest.h"
#include "position.h"

TEST(position_check, test1) {
    position p;
    p.add_to_position(100);
    EXPECT_EQ(100,p.get_position());
    p = p + 100;
    EXPECT_EQ(200,p.get_position());

}

TEST(position_check, test2) {
    position p(100);
    EXPECT_EQ(100,p.get_position());
    p += 100;
    EXPECT_EQ(200,p.get_position());
    p -= 200;
    EXPECT_EQ(0,p.get_position());
}