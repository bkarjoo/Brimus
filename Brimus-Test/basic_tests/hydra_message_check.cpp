//
// Created by b.karjoo on 4/7/2017.
//
#include "gtest/gtest.h"
#include "hydra_message.h"



TEST(hydra_message_tests, test2) {
    const int login_code = 626021100;
    const std::string login = "demo";
    const std::string password = "demo";
    auto msg = hydra_message::make_login_msg(login_code, login, password);
    EXPECT_EQ(35, msg.length());
    EXPECT_EQ("#:00000:I:035:626021100:demo:demo:*", msg);
}

TEST(hydra_message_tests, test3) {
    const int login_code = 626021100;
    const std::string login = "demo";
    const std::string password = "demo";
    auto msg = hydra_message::make_trader_login_msg(login_code, login, password);
    EXPECT_EQ(37, msg.length());
    EXPECT_EQ("#:00000:I:037:626021100:demo:demo:T:*", msg);
}