//
// Created by b.karjoo on 4/5/2017.
//

#ifndef BRIMUS_S_SPYART_H
#define BRIMUS_S_SPYART_H


#include "stdafx.h"
#include "bar_series.h"
#include "btime.h"
#include "instrument.h"
#include "IStrategyRules.h"
#include "strategy_oms.h"


class S_SpyArt : public IStrategyRules {
    // no pointer needed, just own the object
    std::shared_ptr<strategy_oms> oms;
    // instruments, some strategies are one symbol, otherwise you need a vector
    // TODO : should not have instrument, just use global message
    boost::optional<instrument&> SPY;
    // indicators, you need one indicator per instrument
    std::shared_ptr<bar_series> FiveMinBars = nullptr;
    // settings
    static constexpr int SHARES_PER_LEVEL = 100;
    static constexpr int NUMBER_OF_LEVELS = 4;
    static constexpr int MAX_POSITION_SIZE = SHARES_PER_LEVEL * NUMBER_OF_LEVELS;
    static constexpr double MIN_DIST_BET_ORDS = 0.10;
    static constexpr double LIMIT_AWAY = .02;
    // variables
    btime time;
    double bar_close = 0;
    double bar_high = 0;
    double minClose5 = 0;
    double maxClose5 = 0;
    double avgHigh3 = 0;
    double avgLow3 = 0;
    double avgHigh8 = 0;
    double avgLow8 = 0;
    // helper functions
    std::function<void(std::string)> get_callback();
public:
    bool update_on() override;

    S_SpyArt();

    void set_oms(std::shared_ptr<strategy_oms> o) { oms = o; }

    void update(std::string string) override;

    bool long_entry_rules(std::string s) override;

    bool short_entry_rules(std::string s) override;

    bool long_target_rules(std::string s) override;

    bool short_target_rules(std::string s) override;

    bool long_stoploss_rules(std::string s) override;

    bool short_stoploss_rules(std::string s) override;

    void place_long_entry(std::string string) override;

    void place_short_entry(std::string string) override;

    void place_long_target(std::string string) override;

    void place_short_target(std::string string) override;

    void place_long_stoploss(std::string string) override;

    void place_short_stoploss(std::string string) override;


};


#endif //BRIMUS_S_SPYART_H
