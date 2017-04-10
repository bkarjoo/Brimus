
//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_EXECUTION_H
#define BRIMUS_EXECUTION_H
#include "stdafx.h"

class execution {
private:
    int quantity = 0;
    double price = 0.0;
    std::string symbol = "";
    int originalQty = 0;
    double originalPrice = 0.0;
public:
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
};


#endif //BRIMUS_EXECUTION_H