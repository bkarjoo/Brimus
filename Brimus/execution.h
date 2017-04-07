
//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_EXECUTION_H
#define BRIMUS_EXECUTION_H
#include <string>

struct execution {
    int quantity = 0;
    double price = 0.0;
    std::string symbol = "";
    double money_flow() { return -1 * quantity * price; }
    execution(int qty, std::string symb, double prc) :
            quantity(qty), symbol(symb), price(prc) {}
};


#endif //BRIMUS_EXECUTION_H