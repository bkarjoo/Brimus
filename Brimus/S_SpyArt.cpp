//
// Created by b.karjoo on 4/5/2017.
//

#include "S_SpyArt.h"
#include "global_basket.h"

using namespace std;

S_SpyArt::S_SpyArt() {
    // TODO: request indicators required from global basket
    FiveMinBars = std::make_shared<bar_series>("SPY");
    FiveMinBars->setBar_duration(5);
    FiveMinBars->AddNewBarObserver(get_callback());
    auto& gb = global_basket::get_instance();
    // bind give minute bar to SPY so it's updated by itself
    SPY = gb.get_instrument_ptr("SPY");
    if (!SPY) throw std::invalid_argument("instrument not set");
    SPY->setLast_observer(FiveMinBars->get_callback());
}


bool S_SpyArt::long_entry_rules(std::string s) {
    std::cout << std::endl << time.to_string() << std::endl;
    int i = 0;
    if (oms->has_open_buy_orders(s)) {
        // if you are short and trying to exit
        // if you are flat and trying to initiate position
        // if you are long and trying to add to position
        std::cout << "NO CIGAR BECAUSE HAS OPEN BUY ORDER" << std::endl;
        return false;
    }
    std::cout << i++;
    if (oms->get_position(s) >= maxPosition) {
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
    if (!(oms->get_position(s) == 0 ||
         bar_close < oms->last_execution_price(s) - minDistBetweenLongs)) {
        std::cout << "NO CIGAR BECAUSE NOT LOW ENOUGH COMPARED TO PREV BUY" << std::endl;
        return false;
    }
    std::cout << i++ ;
    return true;
}

bool S_SpyArt::short_entry_rules(std::string s) {
    cout << "POSITION: " << oms->get_position(s) << endl;

    if (oms->has_open_sell_orders(s)) {
        cout << "NO CIGAR BECAUSE OPEN BUY ORDER" << endl;
        return false;
    }
    if (oms->get_position(s) <= -maxPosition) {
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
    if (!(oms->get_position(s) == 0 ||
          bar_close > oms->last_execution_price(s) + minDistBetweenShorts)) {
        std::cout << "NO CIGAR BECAUSE NOT LOW ENOUGH COMPARED TO PREV BUY" << std::endl;
        return false;
    }
    return true;
}

bool S_SpyArt::long_target_rules(std::string s) {
    return false;
}

bool S_SpyArt::short_target_rules(std::string s) {
    if (oms->get_position(s) < 0) {

    }
    return false;
}

bool S_SpyArt::long_stoploss_rules(std::string s) {
    return false;
}

bool S_SpyArt::short_stoploss_rules(std::string s) {
    return false;
}



void S_SpyArt::place_long_entry(std::string s) {
    std::cout << "Placing Long Order" << std::endl;
    oms->submit(100,s,bar_close - limitAway);
}

void S_SpyArt::place_short_entry(std::string s) {
    cout << "Placing Short Order" << endl;
    oms->submit(100,s,bar_close + limitAway);
}

void S_SpyArt::place_long_target(std::string s) {

}

void S_SpyArt::place_short_target(std::string s) {

}

void S_SpyArt::place_long_stoploss(std::string s) {

}

void S_SpyArt::place_short_stoploss(std::string s) {

}

void S_SpyArt::update(std::string s) {
    cout << "Symbol " << s << " was updated." << endl;
}

std::function<void(std::string)> S_SpyArt::get_callback() {
    std::function<void(std::string)> callback = [this](std::string symbol) {
        if (FiveMinBars->PreviousBar(1) != nullptr) {
            time = FiveMinBars->PreviousBar(1)->getStartTime();
            bar_close = FiveMinBars->PreviousBar(1)->get_close();
            avgHigh3 = FiveMinBars->AverageHigh(3);
            avgLow3 = FiveMinBars->AverageLow(3);
            avgHigh8 = FiveMinBars->AverageHigh(8);
            avgLow8 = FiveMinBars->AverageLow(8);
            bar_high = FiveMinBars->PreviousBar(1)->get_high();
            minClose5 = FiveMinBars->MinClose(5);
            maxClose5 = FiveMinBars->MaxClose(5);
            if (this->long_stoploss_rules(symbol)) this->place_long_stoploss(symbol);
            if (this->short_stoploss_rules(symbol)) this->place_short_stoploss(symbol);
            if (this->long_entry_rules(symbol)) this->place_long_entry(symbol);
            if (this->short_entry_rules(symbol)) this->place_short_entry(symbol);
            if (this->long_target_rules(symbol)) this->place_long_target(symbol);
            if (this->short_target_rules(symbol)) this->place_short_target(symbol);
        }
     };
    return callback;
}

bool S_SpyArt::update_on() {
    return false;
}
