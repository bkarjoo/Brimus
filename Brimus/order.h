//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_ORDER_H
#define BRIMUS_ORDER_H
#include <string>

class order {
    int quantity = 0;
    std::string symbol = "";
    double price = 0.0;
    int executed_qty = 0;
public:
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

    int getExecuted_qty() const {
        return executed_qty;
    }

    void setExecuted_qty(int executed_qty) {
        order::executed_qty = executed_qty;
    }

    order(int quantity, const std::string &symbol, double price, int executed_qty) : quantity(quantity), symbol(symbol),
                                                                                     price(price),
                                                                                     executed_qty(executed_qty) {}

    order(int qty, std::string symb, double prc) :
            quantity(qty), symbol(symb), price(prc) {}
};


#endif //BRIMUS_ORDER_H