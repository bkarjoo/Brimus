//
// Created by b.karjoo on 3/22/2017.
//

#include "strategy.h"
#include "cap_filepath_maker.h"
#include "stock_collection.h"

using namespace std;

strategy::strategy(unique_ptr<strategy_launch_rules> lr, unique_ptr<strategy_symbol_basket> sb)
{
    launchRules = move(lr);
    symbolBasket = move(sb);
}

run_mode strategy::getRunMode() const {
    return runMode;
}

void strategy::setRunMode(run_mode runMode) {
    strategy::runMode = runMode;
}

const strategy_launch_rules & strategy::getLaunchRules() const {
    return *launchRules;
}

void strategy::on_symbol_updated(const stock& stk, stock_field sf) {
//    cout << symbol << " Last Price: "
//              << global_basket::get_instance().LastPrice(symbol) << endl;
    switch (sf)
    {
        case stock_field::ASK :
            if (rules->update_on_ask()) run_rules(stk);
            break;
        case stock_field::ASK_SIZE:
            if (rules->update_on_ask_size()) run_rules(stk);
            break;
        case stock_field::BID :
            if (rules->update_on_bid()) run_rules(stk);
            break;
        case stock_field::BID_SIZE:
            if (rules->update_on_bid_size()) run_rules(stk);
            break;
        case stock_field::LAST :
            if (rules->update_on_last()) run_rules(stk);
            break;
        case stock_field::LAST_SIZE:
            if (rules->update_on_last_size()) run_rules(stk);
            break;
        case stock_field::OPEN:
            if (rules->update_on_open()) run_rules(stk);
            break;
    }
}

function<void(const stock &, stock_field)>
strategy::get_update_symbol_callback() {
    function<void(const stock &, stock_field)> callback;
    callback = [this](const stock & stk, stock_field sf){
        on_symbol_updated(stk,sf);
    };
    return callback;
}

std::function<void(const bar_series &)>
strategy::get_update_bar_series_callback() {
    function<void(const bar_series &)> callback;
    callback = [this](const bar_series& bs){
        rules->on_bar_series(
                *(stock_collection::get_instance().get_stock(bs.getSymbol())),
            oms, bs);
    };
    return function<void(const bar_series &)>();
}

void strategy::run_rules(const stock &stk) {
    if (rules->long_stoploss_rules(stk, oms)) rules->place_long_stoploss(stk, oms);
    if (rules->short_stoploss_rules(stk, oms)) rules->place_short_stoploss(stk, oms);
    if (rules->long_entry_rules(stk, oms)) rules->place_long_entry(stk, oms);
    if (rules->short_entry_rules(stk, oms)) rules->place_short_entry(stk, oms);
    if (rules->long_target_rules(stk, oms)) rules->place_long_target(stk, oms);
    if (rules->short_target_rules(stk, oms)) rules->place_short_target(stk, oms);
}

const strategy_symbol_basket &strategy::getSymbolBasket() const {
    return *symbolBasket;
}





