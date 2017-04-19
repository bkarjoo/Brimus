//
// Created by b.karjoo on 3/29/2017.
//
#include <stock_collection.h>
#include "gtest/gtest.h"
#include "strategy_oms.h"
#include "market_simulator.h"
#include "cap_message.h"
#include "cap_msg_field.h"
#include "stdafx.h"

using namespace std;


TEST(strategy_oms_tests, test1) {
    strategy_oms oms;
    //oms.submit(100,"SPY",124);

    EXPECT_EQ(1,1);
}

/*
 * strategy oms sends orders to market_simulator
 * therefore both need to be used here
 */
TEST(strategy_oms_tests, send_order)
{

}