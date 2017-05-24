//
// Created by b.karjoo on 5/3/2017.
//

#include "simple_order.h"

simple_order::simple_order(int originalQuantity, const std::string &symbol, double limitPrice) : originalQuantity(
        originalQuantity), symbol(symbol), limitPrice(limitPrice) {}

int simple_order::getOriginalQuantity() const {
    return originalQuantity;
}

const std::string &simple_order::getSymbol() const {
    return symbol;
}

const boost::posix_time::ptime &simple_order::getOrderPlacementTime() const {
    return orderPlacementTime;
}

void simple_order::setOrderPlacementTime(const boost::posix_time::ptime &orderPlacementTime) {
    simple_order::orderPlacementTime = orderPlacementTime;
}

double simple_order::getLimitPrice() const {
    return limitPrice;
}

std::ostream &operator<<(std::ostream &os, const simple_order &order) {
    os << "originalQuantity: " << order.originalQuantity << " symbol: " << order.symbol << " limitPrice: "
       << order.limitPrice << " orderPlacementTime: " << order.orderPlacementTime;
    return os;
}

void simple_order::add_execution(std::shared_ptr<simple_execution> executionPtr) {
    executions.push_back(executionPtr);
}

boost::optional<boost::posix_time::ptime> simple_order::first_execution_time() {
    if (executions.size() == 0) return {};
    return executions[0]->getExecutionTime();
}

boost::optional<boost::posix_time::ptime> simple_order::last_execution_time() {
    if (executions.size() == 0) return {};
    return executions[executions.size()-1]->getExecutionTime();
}

bool simple_order::is_filled() {
    return originalQuantity == executed_quantity();
}

double simple_order::average_execution_price() {
    return total_dollar_value() / executed_quantity();
}

int simple_order::executed_quantity() {
    int execQty = 0;
    for (auto a : executions) execQty += a->getQuantity();
    return execQty;
}

int simple_order::leaves_quantity() {
    return originalQuantity - executed_quantity();
}

double simple_order::total_dollar_value() {
    double val = 0;
    for (auto a : executions) val += a->dollar_value();
    return val;
}


