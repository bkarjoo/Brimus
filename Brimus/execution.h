
//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_EXECUTION_H
#define BRIMUS_EXECUTION_H
#include "stdafx.h"

class execution {
private:
    int quantity = 0;
    std::string symbol = "";
    double price = 0.0;

    // TODO: execution should have no knowledge of order except its id
    std::string id;
    int originalQty = 0;
    double originalPrice = 0.0;
public:
    const std::string &getId() const {
        return id;
    }

    void setId(const std::string &id) {
        execution::id = id;
    }
    int getOriginalQty() const {
        return originalQty;
    }

    void setOriginalQty(int originalQty) {
        execution::originalQty = originalQty;
    }

    double getOriginalPrice() const {
        return originalPrice;
    }

    void setOriginalPrice(double originalPrice) {
        execution::originalPrice = originalPrice;
    }
 
    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        execution::quantity = quantity;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        execution::price = price;
    }

    const std::string &getSymbol() const {
        return symbol;
    }

    void setSymbol(const std::string &symbol) {
        execution::symbol = symbol;
    }

    double money_flow() { return -1 * quantity * price; }
    execution(int qty, std::string symb, double prc) :
            quantity(qty), symbol(symb), price(prc) {}
    execution(int quantity, const std::string &symbol, double price, const std::string &id) :
            quantity(quantity), symbol(symbol), price(price), id(id) {}

};


#endif //BRIMUS_EXECUTION_H