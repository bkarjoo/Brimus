//
// Created by b.karjoo on 3/22/2017.
//

#include "strategy.h"
#include "cap_filepath_maker.h"
#include "stock_collection.h"

using std::cout; using std::endl;using std::string;

/*
 * called by instrument so strategy knows that instrument was updated
 */

// strategy level notify only updates strategy functions like current time
// strategy level notify called by base which overrides it
void strategy::notify(std::string symbol) {

    auto symb = instruments[symbol];
    if (symb == nullptr) return;

    currentTime = symb->getPacketTime();


    if (oms->has_position(symbol)
        && !oms->has_open_orders(symbol)) {
        oms->submit(100,symbol,symb->getBid());
    } else if (oms->get_position(symbol) > 0
        && !oms->has_open_orders(symbol)) {
        oms->submit(-100,symbol,symb->getBid());
    }

    //cout << "Current Time : " << currentTime.to_string() << endl;
}



//void strategy::add_instrument(std::shared_ptr<instrument> i) {
//    string symbol = i->getSymbol();
//    instruments[symbol] = i;
//    //i->set_strategy(this);
//}





const bar_time &strategy::getCurrentTime() const {
    return currentTime;
}

std::function<void(std::shared_ptr<execution>)> strategy::get_callback() {
    std::function<void(std::shared_ptr<execution>)> callback =
            [this] (std::shared_ptr<execution> exec) {
                // find the order

                // adjust its quantity

                // if order is done move it to closed_orders

                // add execution to order and execution stack


                // update position


//                auto quantity = exec->quantity;
//                auto symbol = exec->symbol;
//                auto price = exec->price;
//
//                std::string side = (quantity > 0) ? "bot" : "sold";
//                cout << side << " " << abs(quantity) << " " << symbol << " @" << price
//                     << " position: " << positions[symbol] << " money flow: "
//                        << sum_money_flow(symbol) << " #execs: " << executions[symbol].size() << endl;
//                cout << "Open Position Value: " << open_position_value(symbol) << endl;
//                cout << "P&L: " << pandl(symbol) << endl;
//                cout << "P&L total: " << pandl() << endl;
            };
    return callback;
}



void strategy::setLaunchRules(std::unique_ptr<strategy_launch_rules> launchRules) {
    launchRules = move(launchRules);
}

void strategy::setSymbolBakset(std::unique_ptr<strategy_symbol_basket> symbolBakset) {
    symbolBakset = move(symbolBakset);
}

strategy::strategy(std::unique_ptr<strategy_launch_rules> lr, std::unique_ptr<strategy_symbol_basket> sb)
{
    oms = std::make_shared<strategy_oms>();
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

const strategy_symbol_basket & strategy::getSymbolBakset() const {
    return *symbolBasket;
}

std::function<void(std::string)> strategy::get_symbol_update_callback() {

    std::function<void(std::string)> callback;

    callback = [this](std::string symbol){
        on_symbol_updated(symbol);
    };

    return callback;
}

void strategy::on_symbol_updated(std::string symbol) {
//    std::cout << symbol << " Last Price: "
//              << global_basket::get_instance().LastPrice(symbol) << endl;

    if (rules->update_on()) {
        if (rules->long_stoploss_rules(symbol)) rules->place_long_stoploss(symbol);
        if (rules->short_stoploss_rules(symbol)) rules->place_short_stoploss(symbol);
        if (rules->long_entry_rules(symbol)) rules->place_long_entry(symbol);
        if (rules->short_entry_rules(symbol)) rules->place_short_entry(symbol);
        if (rules->long_target_rules(symbol)) rules->place_long_target(symbol);
        if (rules->short_target_rules(symbol)) rules->place_short_target(symbol);
    }
}

std::function<void(const boost::posix_time::ptime &, const std::string &, stock_field, double)>
strategy::get_extended_update_symbol_callback() {
    std::function<void(const boost::posix_time::ptime &, const string &, stock_field, double)> callback;
    callback = [this](const boost::posix_time::ptime & time, const string & symbol, stock_field field, double value){
        on_symbol_updated(symbol);
    };

    return callback;
}

const strategy_symbol_basket &strategy::getSymbolBasket() const {
    return *symbolBasket;
}



