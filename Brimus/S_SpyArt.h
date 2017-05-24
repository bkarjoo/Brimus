//
// Created by b.karjoo on 4/5/2017.
//

#ifndef BRIMUS_S_SPYART_H
#define BRIMUS_S_SPYART_H


#include "stdafx.h"
#include "bar_series.h"
#include "bar_time.h"
#include "stock.h"
#include "IStrategyRules.h"
#include "strategy_oms.h"


class S_SpyArt : public IStrategyRules {
    std::unique_ptr<bar_series> FiveMinBars = nullptr;
    // settings
    static constexpr int SHARES_PER_LEVEL = 100;
    static constexpr int NUMBER_OF_LEVELS = 4;
    static constexpr int MAX_POSITION_SIZE = SHARES_PER_LEVEL * NUMBER_OF_LEVELS;
    static constexpr double MIN_DIST_BET_ORDS = 0.10;
    static constexpr double LIMIT_AWAY = .02;
    // variables
    bar_time time = bar_time("00000000");
    double bar_close = 0;
    double bar_high = 0;
public:
    void run_rules(const stock &stock1, strategy_oms &oms) override;

private:
    double minClose5 = 0;
    double maxClose5 = 0;
    double avgHigh3 = 0;
    double avgLow3 = 0;
    double avgHigh8 = 0;
    double avgLow8 = 0;

public:

    S_SpyArt();

    bool long_entry_rules(const stock& s, const strategy_oms& o) override;

    bool short_entry_rules(const stock& s, const strategy_oms& o) override;

    bool long_target_rules(const stock& s, const strategy_oms& o) override;

    bool short_target_rules(const stock& s, const strategy_oms& o) override;

    bool long_stoploss_rules(const stock& s, const strategy_oms& o) override;

    bool short_stoploss_rules(const stock& s, const strategy_oms& o) override;

    void place_long_entry(const stock& s, strategy_oms& o) override;

    void place_short_entry(const stock& s, strategy_oms& o) override;

    void place_long_target(const stock& s, strategy_oms& o) override;

    void place_short_target(const stock& s, strategy_oms& o) override;

    void place_long_stoploss(const stock& s, strategy_oms& o) override;

    void place_short_stoploss(const stock& s, strategy_oms& o) override;

    bool update_on_last() override;

    bool update_on_bid() override;

    bool update_on_ask() override;

    bool update_on_last_size() override;

    bool update_on_bid_size() override;

    bool update_on_ask_size() override;

    bool update_on_bar_series() override;

    bool update_on_open() override;

    void on_open(const stock &stock1, const strategy_oms &oms) override;

    void on_bar_series(const stock &stock1, strategy_oms &oms, const bar_series &series) override;

};


#endif //BRIMUS_S_SPYART_H
