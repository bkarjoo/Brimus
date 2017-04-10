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
    std::function<void(std::string)> get_callback();
    std::shared_ptr<strategy_oms> oms;
    std::shared_ptr<instrument> SPY;
    std::shared_ptr<bar_series> FiveMinBars = nullptr;
    btime time;
    int maxPosition = 400; // 4 levels of 100 each
    double bar_close = 0;
    double bar_high = 0;
    double minClose5 = 0;
    double maxClose5 = 0;
    double avgHigh3 = 0;
    double avgLow3 = 0;
    double avgHigh8 = 0;
    double avgLow8 = 0;
    static constexpr double minDistBetweenLongs = 0.10;
    static constexpr double minDistBetweenShorts = 0.10;
    static constexpr double limitAway = .02;
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
