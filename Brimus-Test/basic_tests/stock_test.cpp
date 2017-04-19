//
// Created by b.karjoo on 4/19/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "stock.h"
#include <boost/date_time/posix_time/posix_time_duration.hpp>
using namespace std;

TEST(stock_tests, constructor) {
    stock s;
    stock s2("IBM");
    EXPECT_EQ("IBM",s2.Symbol());
}

TEST(stock_tests, tick_update) {
    stock s("IBM");
    cap_message sm;
    string* symb = new string("IBM");
    sm.set_symbol(*symb);
    cap_msg_field cmf;
    cmf.field_code = ('t');
    cmf.field_value = "125.12";
    sm.add_field(cmf.field_code,cmf.field_code_value,cmf.field_value, cmf.field_exchange);
    s.tick_update(sm);
    EXPECT_EQ("IBM",s.Symbol());
    EXPECT_DOUBLE_EQ(125.12,s.Last());
}

TEST(stock_test,time_update) {
    stock s("IBM");
    cap_message sm;
    string* symb = new string("IBM");
    sm.set_symbol(*symb);
    cap_msg_field cmf;
    cmf.field_code = ('t');
    cmf.field_value = "125.12";
    sm.add_field(cmf.field_code,cmf.field_code_value,cmf.field_value, cmf.field_exchange);
    s.tick_update(sm);
    s.time_update(boost::posix_time::second_clock::local_time());
    EXPECT_EQ(boost::posix_time::second_clock::local_time().time_of_day().hours(),s.Time().time_of_day().hours());
}

//void tick_update(std::unique_ptr<cap_message>);
//void tick_update(const cap_message&);
//void time_update(boost::posix_time::ptime _packetTime);
//// getters
//const std::string &Symbol() const;
//price Last() const;
//price Ask() const;
//price Bid() const;
//price Open() const;
//size LastSize() const;
//size AskSize() const;
//size BidSize() const;
//const ptime &Time() const;
//// constructor
//stock(const std::string &symbol);
//stock(){};
//void setSymbol(const std::string& symb) { symbol = symb; }