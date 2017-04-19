//
// Created by b.karjoo on 4/5/2017.
//

#ifndef BRIMUS_ISTRATEGYRULES_H
#define BRIMUS_ISTRATEGYRULES_H

#include "stdafx.h"
#include "strategy_oms.h"
#include "stock.h"
#include "bar_series.h"

class IStrategyRules {
public:
    virtual bool update_on_last() = 0;
    virtual bool update_on_bid() = 0;
    virtual bool update_on_ask() = 0;
    virtual bool update_on_last_size() = 0;
    virtual bool update_on_bid_size() = 0;
    virtual bool update_on_ask_size() = 0; 
    virtual bool update_on_open() = 0;
    virtual bool update_on_bar_series() = 0;

    virtual void on_open(const stock&, const strategy_oms&) = 0;
    virtual void on_bar_series(const stock &, strategy_oms &, const bar_series &) = 0;
    
    virtual bool long_entry_rules(const stock&, const strategy_oms&) = 0;
    virtual bool short_entry_rules(const stock&, const strategy_oms&) = 0;
    virtual bool long_target_rules(const stock&, const strategy_oms&) = 0;
    virtual bool short_target_rules(const stock&, const strategy_oms&) = 0;
    virtual bool long_stoploss_rules(const stock&, const strategy_oms&) = 0;
    virtual bool short_stoploss_rules(const stock&, const strategy_oms&) = 0;

    virtual void place_long_entry(const stock&, strategy_oms&) = 0;
    virtual void place_short_entry(const stock&, strategy_oms&) = 0;
    virtual void place_long_target(const stock&, strategy_oms&) = 0;
    virtual void place_short_target(const stock&, strategy_oms&) = 0;
    virtual void place_long_stoploss(const stock&, strategy_oms&) = 0;
    virtual void place_short_stoploss(const stock&, strategy_oms&) = 0;
    
    virtual void run_rules(const stock& stk, strategy_oms& oms)
    {
        if (long_stoploss_rules(stk, oms)) place_long_stoploss(stk, oms);
        if (short_stoploss_rules(stk, oms)) place_short_stoploss(stk, oms);
        if (long_entry_rules(stk, oms)) place_long_entry(stk, oms);
        if (short_entry_rules(stk, oms)) place_short_entry(stk, oms);
        if (long_target_rules(stk, oms)) place_long_target(stk, oms);
        if (short_target_rules(stk, oms)) place_short_target(stk, oms);
    }
};



#endif //BRIMUS_ISTRATEGYRULES_H
