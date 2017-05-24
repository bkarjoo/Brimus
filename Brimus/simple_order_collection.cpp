//
// Created by b.karjoo on 5/3/2017.
//

#include "simple_order_collection.h"
using namespace std;

double simple_order_collection::average_price() {
    int qty = 0;
    double val = 0;
    for (auto a : orders) {
        val += a->total_dollar_value();
        qty += a->executed_quantity();
    }
    return val/qty;
}

int simple_order_collection::execution_quantity() {
    int qty;
    for (auto a : orders) qty += a->executed_quantity();
    return qty;
}

boost::optional<boost::posix_time::ptime>
simple_order_collection::first_execution_time() {
    if (orders.size() == 0) return {};
    if (orders[0]->executed_quantity() == 0) return {};
    return orders[0]->first_execution_time();
}

boost::optional<boost::posix_time::ptime>
simple_order_collection::last_execution_time() {
    if (orders.size() == 0) return {};
    if (orders[orders.size()-1]->executed_quantity() == 0) return {};
    return orders[orders.size()-1]->last_execution_time();
}

void simple_order_collection::add_order(simple_order_collection::order_ptr o) {
    orders.push_back(o);
}

boost::optional<std::string> simple_order_collection::get_symbol() {
    if (orders.size() == 0) return {};
    return orders[0]->getSymbol();
}

boost::optional<std::string> simple_order_collection::get_side() {
    if (orders.size() == 0) return {};
    string l = "Long";
    string s = "Short";
    return orders[0]->getOriginalQuantity() > 0 ? l : s;
}

double simple_order_collection::dollar_value() {
    double qty = 0;
    for (auto a : orders) qty += a->total_dollar_value();
    return qty;
}


