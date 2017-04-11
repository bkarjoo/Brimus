//
// Created by b.karjoo on 4/11/2017.
//

#include "ms_execution.h"

ms_execution::ms_execution(int quantity, const std::string &symbol, double price) : quantity(quantity), symbol(symbol),
                                                                                    price(price) {}

int ms_execution::getQuantity() const {
    return quantity;
}

void ms_execution::setQuantity(int quantity) {
    ms_execution::quantity = quantity;
}

const std::string &ms_execution::getSymbol() const {
    return symbol;
}

void ms_execution::setSymbol(const std::string &symbol) {
    ms_execution::symbol = symbol;
}

double ms_execution::getPrice() const {
    return price;
}

void ms_execution::setPrice(double price) {
    ms_execution::price = price;
}
