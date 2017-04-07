//
// Created by b.karjoo on 3/22/2017.
//

#ifndef BRIMUS_STRATEGY_H
#define BRIMUS_STRATEGY_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "market_simulator.h"
#include "execution.h"
#include "btime.h"
#include "instrument_observer.h"
#include "strategy_oms.h"
#include "launch_rules.h"
#include "symbol_basket.h"
#include "IStrategyRules.h"


class instrument;

enum class run_mode { LIVE, BACKTEST };

class strategy {
protected:
    run_mode runMode = run_mode::BACKTEST;
    std::shared_ptr<strategy_oms> oms;
    std::shared_ptr<launch_rules> launchRules;
    std::shared_ptr<symbol_basket> symbolBakset;
    std::shared_ptr<IStrategyRules> rules;
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
    // getter setters
    run_mode getRunMode() const;
    void setRunMode(run_mode runMode);
    void setRules(std::shared_ptr<IStrategyRules> r) { rules = r; rules->set_oms(oms); }
};


#endif //BRIMUS_STRATEGY_H
