//
// Created by b.karjoo on 3/29/2017.
//

#include "strategy_oms.h"
#include "global_basket.h"

using namespace std;

bool strategy_oms::has_position(std::string symbol) {
    return positions.has_position(symbol);
}

bool strategy_oms::has_open_orders(std::string symbol) {
    return open_orders.has_open_order(symbol);
}

bool strategy_oms::has_open_buy_orders(std::string symbol) {
    return open_orders.has_open_buy_order(symbol);
}

bool strategy_oms::has_open_sell_orders(std::string symbol) {
    return open_orders.has_open_sell_order(symbol);
}

int strategy_oms::get_position(std::string symbol) {
    return positions.get_position(symbol);
}

double strategy_oms::sum_money_flow(std::string symbol) {
    return executions.sum_money_flow(symbol);
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
    return 0;
}

double strategy_oms::pandl(std::string symbol) {
    return 0;
}

double strategy_oms::pandl() {
    return 0;
}

void strategy_oms::submit(int qty, std::string symbol, double price) {
    std::cout << "SUBMITING ORDER" << std::endl;
    open_orders.add_order(std::make_shared<order>(qty,symbol,price));
    cout << "OPEN ORDER COUNT: " << open_orders.size() << endl;
    market_simulator::get_instance().send_order(qty,symbol,price,this);
}

void strategy_oms::on_execution(int execQty, const std::string &symbol, double price, int orig_qty, double orig_price) {
    // find my order
    auto order_ptr = open_orders.find_order(orig_qty,symbol,orig_price);
    cout << "OPEN ORDERS COUNT: " << open_orders.size() << endl;
    if (order_ptr == nullptr) return;
    order_ptr->setExecuted_qty(order_ptr->getExecuted_qty() + execQty);
    if (order_ptr->getQuantity() == order_ptr->getExecuted_qty())
        closed_orders.add_order(open_orders.fetch_remove_order(orig_qty,symbol,price));
    positions.add_position(symbol, execQty);
}

double strategy_oms::last_execution_price(std::string symbol) {
    return executions.last_fill_price(symbol);
}


