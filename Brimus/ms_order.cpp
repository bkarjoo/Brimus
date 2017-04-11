//
// Created by b.karjoo on 4/11/2017.
//

#include "ms_order.h"

using namespace std;

int ms_order::getQuantity() const {
    return quantity;
}

void ms_order::setQuantity(int quantity) {
    ms_order::quantity = quantity;
}

const std::string &ms_order::getSymbol() const {
    return symbol;
}

void ms_order::setSymbol(const std::string &symbol) {
    ms_order::symbol = symbol;
}

double ms_order::getPrice() const {
    return price;
}

void ms_order::setPrice(double price) {
    ms_order::price = price;
}

const std::function<void(int, std::string, double, std::string)> &ms_order::getCallback() const {
    return callback;
}

void ms_order::setCallback(const std::function<void(int, std::string, double, std::string)> &callback) {
    ms_order::callback = callback;
}


const std::string &ms_order::getId() const {
    return id;
}

void ms_order::setId(const std::string &id) {
    ms_order::id = id;
}

ms_order::ms_order(int quantity, const std::string &symbol, double price, const std::string &id,
                   const std::function<void(int, std::string, double, std::string)> &callback) : quantity(quantity),
                                                                                                 symbol(symbol),
                                                                                                 price(price), id(id),
                                                                                                 callback(callback) {}

ms_order::ms_order(int quantity, const std::string &symbol, double price, const std::string &id) : quantity(quantity),
                                                                                                   symbol(symbol),
                                                                                                   price(price),
                                                                                                   id(id) {}

void ms_order::add_execution(int qty, double price) {
    auto exec = make_unique<ms_execution>(qty, symbol, price);
    executions.add_execution(move(exec));
}

int ms_order::execution_qty() {
    int sum = 0;
    for (auto it = executions.begin(); it != executions.end(); ++it)
    {
        sum += (*it)->getQuantity();
    }
    return sum;
}

bool ms_order::is_filled() {
    return execution_qty() == quantity;
}

int ms_order::remain_qty() {
    return quantity - execution_qty();
}
