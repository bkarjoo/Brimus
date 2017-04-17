//
// Created by b.karjoo on 3/22/2017.
//

#ifndef BRIMUS_STRATEGY_H
#define BRIMUS_STRATEGY_H

#include "stdafx.h"
#include "market_simulator.h"
#include "execution.h"
#include "btime.h"
#include "strategy_oms.h"
#include "launch_rules.h"
#include "symbol_basket.h"
#include "IStrategyRules.h"
#include "stock_field.h"


class instrument;

enum class run_mode { LIVE, BACKTEST };

class strategy {
protected:
    run_mode runMode = run_mode::BACKTEST;
    // TODO : all these shared_ptrs shouldn't be pointers at all
    // oms shared between rules and strategy class
    std::shared_ptr<strategy_oms> oms;
    // launch rules need to be shared
    std::shared_ptr<launch_rules> launchRules;
    std::shared_ptr<symbol_basket> symbolBakset;
    std::shared_ptr<IStrategyRules> rules;
    // TODO : a strategy shouldn't have instruments, just update callback
    // TODO : a less sensitive strategy can have an on second call back
    // TODO : an even less sensitive strategy can be just responding to completion of a bar series
    // note stop orders are handled by the market simulator which checks against every tick
    std::map<std::string, std::shared_ptr<instrument> > instruments;
    btime currentTime;
    std::function<void(std::shared_ptr<execution>)> get_callback();
    void on_symbol_updated(std::string basic_string);
public:
    strategy(const std::shared_ptr<launch_rules> &launchRules, const std::shared_ptr<symbol_basket> &symbolBakset);
    const btime &getCurrentTime() const;
    void notify(std::string);
    // void add_instrument(std::shared_ptr<instrument>);
    void setLaunchRules(const std::shared_ptr<launch_rules> &launchRules);
    void setSymbolBakset(const std::shared_ptr<symbol_basket> &symbolBakset);
    const std::shared_ptr<launch_rules> &getLaunchRules() const;
    const std::shared_ptr<symbol_basket> &getSymbolBakset() const;
    std::function<void(std::string)> get_symbol_update_callback();
    std::function<void(const boost::posix_time::ptime &, const std::string &, stock_field, double)> get_extended_update_symbol_callback();
    // getter setters
    run_mode getRunMode() const;
    void setRunMode(run_mode runMode);
    void setRules(std::shared_ptr<IStrategyRules> r) { rules = r; rules->set_oms(oms); }
};


#endif //BRIMUS_STRATEGY_H
