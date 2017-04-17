
//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_EXECUTION_H
#define BRIMUS_EXECUTION_H
#include "stdafx.h"

class execution {
private:
    int execQty = 0;
    std::string symbol = "";
    double execPrice = 0.0;
    std::string id;
public:
    const std::string &getId() const {
        return id;
    }

    void setId(const std::string &id) {
        execution::id = id;
    }
 
    int getQuantity() const {
        return execQty;
    }

    void setQuantity(int quantity) {
        execution::execQty = quantity;
    }

    double getPrice() const {
        return execPrice;
    }

    void setPrice(double price) {
        execution::execPrice = price;
    }

    const std::string &getSymbol() const {
        return symbol;
    }

    void setSymbol(const std::string &symbol) {
        execution::symbol = symbol;
    }

    double money_flow() const { return -1 * execQty * execPrice; }
    execution(int qty, std::string symb, double prc) :
            execQty(qty), symbol(symb), execPrice(prc) {}
    execution(int quantity, const std::string &symbol, double price, const std::string &id) :
            execQty(quantity), symbol(symbol), execPrice(price), id(id) {}

};


#endif //BRIMUS_EXECUTION_H