//
// Created by b.karjoo on 5/3/2017.
//

#include "simple_execution.h"

simple_execution::simple_execution(int quantity, const std::string &symbol, double fillPrice,
                                   const boost::posix_time::ptime &executionTime) : quantity(quantity), symbol(symbol),
                                                                                    fillPrice(fillPrice),
                                                                                    executionTime(executionTime) {}

int simple_execution::getQuantity() const {
    return quantity;
}

std::ostream &operator<<(std::ostream &os, const simple_execution &execution) {
    os << "quantity: " << execution.quantity << " symbol: " << execution.symbol << " fillPrice: " << execution.fillPrice
       << " executionTime: " << execution.executionTime;
    return os;
}

const std::string &simple_execution::getSymbol() const {
    return symbol;
}

double simple_execution::getFillPrice() const {
    return fillPrice;
}

const boost::posix_time::ptime &simple_execution::getExecutionTime() const {
    return executionTime;
}

double simple_execution::dollar_value() {
    return fillPrice * quantity;
}

