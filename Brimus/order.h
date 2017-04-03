//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_ORDER_H
#define BRIMUS_ORDER_H
#include <string>

struct order {
    int quantity = 0;
    std::string symbol = "";
    double price = 0.0;
};


#endif //BRIMUS_ORDER_H