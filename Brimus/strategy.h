//
// Created by b.karjoo on 3/22/2017.
//

#ifndef BRIMUS_STRATEGY_H
#define BRIMUS_STRATEGY_H

#include "stdafx.h"
#include "market_simulator.h"
#include "execution.h"
#include "bar_time.h"
#include "strategy_oms.h"
#include "strategy_launch_rules.h"
#include "strategy_symbol_basket.h"
#include "IStrategyRules.h"
#include "stock_field.h"
#include "stock.h"


class instrument;

enum class run_mode { LIVE, BACKTEST };

class strategy {
    run_mode runMode = run_mode::BACKTEST;
    strategy_oms oms;
    std::unique_ptr<strategy_launch_rules> launchRules;
    std::unique_ptr<strategy_symbol_basket> symbolBasket;
    std::unique_ptr<IStrategyRules> rules;
    // TODO : a strategy shouldn't have instruments, just update callback
    // TODO : a strategy shouldn't have indicators, just update callback

    void on_symbol_updated(const stock& stk, stock_field sf);
public:
    strategy(std::unique_ptr<strategy_launch_rules> launchRules,
             std::unique_ptr<strategy_symbol_basket> symbolBakset);
    ~strategy() {}

    const strategy_symbol_basket &getSymbolBasket() const;

    const strategy_launch_rules & getLaunchRules() const;
    std::function<void(const stock&, stock_field)> get_update_symbol_callback();
    std::function<void(const bar_series&)> get_update_bar_series_callback();
    // getter setters
    run_mode getRunMode() const;
    void setRunMode(run_mode runMode);
    void setRules(std::unique_ptr<IStrategyRules> r) { rules = move(r); };

    void run_rules(const stock &stk);
};


#endif //BRIMUS_STRATEGY_H
