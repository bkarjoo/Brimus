//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_ORDER_H
#define BRIMUS_ORDER_H
#include "stdafx.h"
#include "strategy_order_type.h"



class order {

    int quantity = 0;
    std::string symbol = "";
    double price = 0.0;
    std::string id = "";
    strategy_order_type oType;

public:

    strategy_order_type getOType() const {
        return oType;
    }

    void setOType(strategy_order_type oType) {
        order::oType = oType;
    }

    const std::string &getId() const {
        return id;
    }

    void setId(const std::string &id) {
        order::id = id;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        order::quantity = quantity;
    }

    const std::string &getSymbol() const {
        return symbol;
    }

    void setSymbol(const std::string &symbol) {
        order::symbol = symbol;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        order::price = price;
    }

    order(int qty, std::string symb, double prc) :
            quantity(qty), symbol(symb), price(prc) {}

    order(int quantity, const std::string &symbol, double price, strategy_order_type oType) : quantity(
            quantity), symbol(symbol), price(price), oType(oType) {}

};


#endif //BRIMUS_ORDER_H