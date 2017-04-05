//
// Created by b.karjoo on 4/5/2017.
//

#include "S_SpyArt.h"
#include "global_basket.h"
#include <iostream>

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
    std::cout << time.to_string() << std::endl;
    std::cout << FiveMinBars->AverageLow(3) << std::endl;
    std::cout << (bar_close < avgLow3) << std::endl;

    return time.isGreaterThan("094959")
            && time.isLessThan("120000")
            && !(time.isGreaterThan("105959")
                && time.isLessThan("113000"))
            ;
}

bool S_SpyArt::short_entry_rules(std::string s) {
    return false;
}

bool S_SpyArt::long_target_rules(std::string s) {
    return false;
}

bool S_SpyArt::short_target_rules(std::string s) {
    return false;
}

bool S_SpyArt::long_stoploss_rules(std::string s) {
    return false;
}

bool S_SpyArt::short_stoploss_rules(std::string s) {
    return false;
}



void S_SpyArt::place_long_entry(std::string string) {

}

void S_SpyArt::place_short_entry(std::string string) {

}

void S_SpyArt::place_long_target(std::string string) {

}

void S_SpyArt::place_short_target(std::string string) {

}

void S_SpyArt::place_long_stoploss(std::string string) {

}

void S_SpyArt::place_short_stoploss(std::string string) {

}

void S_SpyArt::update(std::string string) {

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
