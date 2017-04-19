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
protected:
    run_mode runMode = run_mode::BACKTEST;
    // TODO : all these shared_ptrs shouldn't be pointers at all
    // oms shared between rules and strategy class
    std::shared_ptr<strategy_oms> oms;
    // launch rules need to be shared
    std::unique_ptr<strategy_launch_rules> launchRules;
    std::unique_ptr<strategy_symbol_basket> symbolBasket;
    std::shared_ptr<IStrategyRules> rules;
    // TODO : a strategy shouldn't have instruments, just update callback
    // TODO : a less sensitive strategy can have an on second call back
    // TODO : an even less sensitive strategy can be just responding to completion of a bar series
    // note stop orders are handled by the market simulator which checks against every tick
    std::map<std::string, std::shared_ptr<stock> > instruments;
    boost::posix_time::ptime currentTime;
    std::function<void(std::shared_ptr<execution>)> get_callback();
    void on_symbol_updated(std::string basic_string);
public:
    strategy(std::unique_ptr<strategy_launch_rules> launchRules, std::unique_ptr<strategy_symbol_basket> symbolBakset);
    ~strategy() {}
    const bar_time &getCurrentTime() const;
    void notify(std::string);
    // void add_instrument(std::shared_ptr<instrument>);
    void setLaunchRules(std::unique_ptr<strategy_launch_rules> launchRules);
    void setSymbolBakset(std::unique_ptr<strategy_symbol_basket> symbolBakset);
    const strategy_launch_rules & getLaunchRules() const;
    const strategy_symbol_basket & getSymbolBakset() const;
    std::function<void(std::string)> get_symbol_update_callback();
    std::function<void(const boost::posix_time::ptime &, const std::string &, stock_field, double)> get_extended_update_symbol_callback();
    // getter setters
    run_mode getRunMode() const;
    void setRunMode(run_mode runMode);
    void setRules(std::shared_ptr<IStrategyRules> r) { rules = r; rules->set_oms(oms); }
    const strategy_symbol_basket& getSymbolBasket() const;
};


#endif //BRIMUS_STRATEGY_H
