//
// Created by b.karjoo on 4/5/2017.
//

#include "S_SpyArt.h"
#include "stock_collection.h"

using namespace std;

S_SpyArt::S_SpyArt() {

}

bool S_SpyArt::long_entry_rules(const stock& s, const strategy_oms& o) {
    std::cout << std::endl << time.to_string() << std::endl;
    int i = 0;
    if (o.has_open_buy_orders(s.Symbol())) {
        // if you are short and trying to exit
        // if you are flat and trying to initiate position
        // if you are long and trying to add to position
        std::cout << "NO CIGAR BECAUSE HAS OPEN BUY ORDER" << std::endl;
        return false;
    }
    std::cout << i++;
    if (o.get_position(s.Symbol()) >= MAX_POSITION_SIZE) {
        std::cout << "NO CIGAR BECAUSE HAS MAX SHARES ALLOWED" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!time.isGreaterThan("094959")) {
        std::cout << "NO CIGAR BECAUSE TOO EARLY" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!time.isLessThan("120000")) {
        std::cout << "NO CIGAR BECAUSE TOO LATE" << std::endl;
        return false;
    }
    std::cout << i++;
    if ((time.isGreaterThan("105959")
           && time.isLessThan("113000"))) {
        std::cout << "NO CIGAR BECAUSE DNT TIME ZONE" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!(bar_close < avgLow3)) {
        std::cout << "NO CIGAR BECAUSE NOT LOWER THAN AvgLow3" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!(bar_high < avgHigh3)) {
        std::cout << "NO CIGAR BECAUSE Reversal Bar" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!(bar_close == minClose5)) {
        std::cout << "NO CIGAR BECAUSE NOT LOWEST CLOSE" << std::endl;
        return false;
    }
    std::cout << i++;
    if (!(o.get_position(s.Symbol()) == 0 ||
         bar_close < o.last_execution_price(s.Symbol()) - MIN_DIST_BET_ORDS)) {
        std::cout << "NO CIGAR BECAUSE NOT LOW ENOUGH COMPARED TO PREV BUY" << std::endl;
        return false;
    }
    std::cout << i++ ;
    return true;
}

bool S_SpyArt::short_entry_rules(const stock& s, const strategy_oms& o) {
    cout << "POSITION: " << o.get_position(s.Symbol()) << endl;

    if (o.has_open_sell_orders(s.Symbol())) {
        cout << "NO CIGAR BECAUSE OPEN BUY ORDER" << endl;
        return false;
    }
    if (o.get_position(s.Symbol()) <= -MAX_POSITION_SIZE) {
        std::cout << "NO CIGAR BECAUSE HAS MAX SHARES ALLOWED" << std::endl;
        return false;
    }
    if (!time.isGreaterThan("094959")) {
        std::cout << "NO CIGAR BECAUSE TOO EARLY" << std::endl;
        return false;
    }
    if (!time.isLessThan("120000")) {
        std::cout << "NO CIGAR BECAUSE TOO LATE" << std::endl;
        return false;
    }
    if ((time.isGreaterThan("105959")
         && time.isLessThan("113000"))) {
        std::cout << "NO CIGAR BECAUSE DNT TIME ZONE" << std::endl;
        return false;
    }
    if (!(bar_close > avgHigh3)) {
        std::cout << "NO CIGAR BECAUSE NOT LOWER THAN AvgLow3" << std::endl;
        return false;
    }
    if (!(bar_high > avgLow3)) {
        std::cout << "NO CIGAR BECAUSE Reversal Bar" << std::endl;
        return false;
    }
    if (!(bar_close == maxClose5)) {
        std::cout << "NO CIGAR BECAUSE NOT HIGHEST CLOSE" << std::endl;
        return false;
    }
    if (!(o.get_position(s.Symbol()) == 0 ||
          bar_close > o.last_execution_price(s.Symbol()) + MIN_DIST_BET_ORDS)) {
        std::cout << "NO CIGAR BECAUSE NOT LOW ENOUGH COMPARED TO PREV BUY" << std::endl;
        return false;
    }
    return true;
}

bool S_SpyArt::long_target_rules(const stock& s, const strategy_oms& o) {
    auto position = o.get_position(s.Symbol());
    return position > 0;
}

bool S_SpyArt::short_target_rules(const stock& s, const strategy_oms& o) {
    auto position = o.get_position(s.Symbol());
    return position < 0;
}

bool S_SpyArt::long_stoploss_rules(const stock& s, const strategy_oms& o) {
    // this strategy has no stop
}

bool S_SpyArt::short_stoploss_rules(const stock& s, const strategy_oms& o) {
    // this strategy has no stop
}
 
void S_SpyArt::place_long_entry(const stock& s, strategy_oms& o) {
    std::cout << "Placing Long Order" << std::endl;
    o.buy_entry(100,s.Symbol(),bar_close - LIMIT_AWAY);
}

void S_SpyArt::place_short_entry(const stock& s, strategy_oms& o) {
    cout << "Placing Short Order" << endl;
    o.short_entry(100,s.Symbol(),bar_close + LIMIT_AWAY);
}

void S_SpyArt::place_long_target(const stock& s, strategy_oms& o) {
    if (o.has_open_sell_orders(s.Symbol())) {
        o.cancel_replace_sell_target(abs(o.get_position(s.Symbol())),s.Symbol(),avgHigh8);
    } else {
        o.sell_target(abs(o.get_position(s.Symbol())),s.Symbol(),avgHigh8);
    }
}

void S_SpyArt::place_short_target(const stock& s, strategy_oms& o) {
    if (o.has_open_buy_orders(s.Symbol())) {
        o.cancel_replace_buy_target(abs(o.get_position(s.Symbol())),s.Symbol(),avgHigh8);
    } else {
        o.buy_target(abs(o.get_position(s.Symbol())),s.Symbol(),avgHigh8);
    }
}

void S_SpyArt::place_long_stoploss(const stock& s, strategy_oms& o) {

}

void S_SpyArt::place_short_stoploss(const stock& s, strategy_oms& o) {

}



void S_SpyArt::on_open(const stock &stock1, const strategy_oms &oms) {

}

void S_SpyArt::on_bar_series(const stock &stk, strategy_oms &oms, const bar_series &FiveMinuteBars) {
    // update the bars dependent vars
    if (FiveMinBars->PreviousBar(1)) {
        time = FiveMinBars->PreviousBar(1)->getStartTime();
        bar_close = FiveMinBars->PreviousBar(1)->Close();
        avgHigh3 = FiveMinBars->AverageHigh(3);
        avgLow3 = FiveMinBars->AverageLow(3);
        avgHigh8 = FiveMinBars->AverageHigh(8);
        avgLow8 = FiveMinBars->AverageLow(8);
        bar_high = FiveMinBars->PreviousBar(1)->High();
        minClose5 = FiveMinBars->MinClose(5);
        maxClose5 = FiveMinBars->MaxClose(5);
        run_rules(stk,oms);
    }
}

bool S_SpyArt::update_on_last() {
    return false;
}

bool S_SpyArt::update_on_bid() {
    return false;
}

bool S_SpyArt::update_on_ask() {
    return false;
}

bool S_SpyArt::update_on_last_size() {
    return false;
}

bool S_SpyArt::update_on_bid_size() {
    return false;
}

bool S_SpyArt::update_on_ask_size() {
    return false;
}

bool S_SpyArt::update_on_bar_series() {
    return false;
}

bool S_SpyArt::update_on_open() {
    return false;
}

void S_SpyArt::run_rules(const stock &stock1, strategy_oms &oms) {
    IStrategyRules::run_rules(stock1, oms);
}
