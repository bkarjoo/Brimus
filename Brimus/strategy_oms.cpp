//
// Created by b.karjoo on 3/29/2017.
//

#include "strategy_oms.h"
#include "global_basket.h"

bool strategy_oms::has_position(std::string symbol) {
    int pos = positions[symbol] != 0;
}

bool strategy_oms::has_open_orders(std::string symbol) {
    return open_orders.find(symbol) != open_orders.end();
}

int strategy_oms::get_position(std::string symbol) {
    return positions[symbol];
}

double strategy_oms::sum_money_flow(std::string symbol) {
    double sum = 0.0;
    for (auto& a : executions[symbol]) {
        sum += a->money_flow();
    }
    return sum;
}

double strategy_oms::sum_money_flow(const std::vector<std::string>& symbols) {
    double sum = 0.0;
    for (auto& a : symbols) {
        sum += sum_money_flow(a);
    }
}

double strategy_oms::open_position_value(std::string symbol) {
    int position = get_position(symbol);
    auto &gb = global_basket::get_instance();
    double last = gb.LastPrice(symbol);
    return position * last;
}

double strategy_oms::open_position_value() {
    double sum = 0.0;
    for (auto& a : positions) {
        sum += open_position_value(a.first);
    }
    return sum;
}

double strategy_oms::pandl(std::string symbol) {
    return sum_money_flow(symbol) + open_position_value(symbol);
}

double strategy_oms::pandl() {
    double sum = 0.0;
    for (auto& a : positions) {
        sum += (sum_money_flow(a.first) + open_position_value(a.first));
    }
    return sum;
}