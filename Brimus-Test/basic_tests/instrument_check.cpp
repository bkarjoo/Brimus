//
// Created by b.karjoo on 4/11/2017.
//
#include "gtest/gtest.h"
#include "instrument.h"
#include "st_message.h"
#include "st_field.h"


using namespace std;
/*
 * what's the difference between the two constructors?
 *
 * one takes a callback function, the other doesn't
 */
TEST(instrument_tests, constructor1)
{
    instrument spy("SPY");
    st_message m;
    std::string s = "SPY", s2 = "", s3 = "129.32";
    char a = 't', b = 0;
    auto msg = make_unique<st_message>();
    st_field f;
    msg->set_symbol(s);
    msg->add_field(a,s2,s3,b);
    spy.on_message(move(msg));
    double last = spy.getLast_price();
    EXPECT_DOUBLE_EQ(129.32,last);
}

TEST(instrument_tests, constructor2)
{

}

TEST(instrument_tests, setLastObserver)
{

}

TEST(instrument_tests, setUpdateObserver)
{

}

TEST(instrument_tests, getLastTimestamp)
{

}

TEST(instrument_tests, getLastPrice)
{

}

TEST(instrument_tests, getLastSize)
{

}

TEST(instrument_tests, getAskPrice)
{

}

TEST(instrument_tests, getBidPrice)
{

}

TEST(instrument_tests, getBidSize)
{

}

TEST(instrument_tests, getOpenPrice)
{

}

TEST(instrument_tests, getClosePrice)
{

}

TEST(instrument_tests, setOutputPath)
{

}

TEST(instrument_tests, getSymbol)
{

}

TEST(instrument_tests, onMessage)
{

}
