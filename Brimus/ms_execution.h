//
// Created by b.karjoo on 4/11/2017.
//

#ifndef BRIMUS_MS_EXECUTION_H
#define BRIMUS_MS_EXECUTION_H
#include "stdafx.h"

class ms_execution {
    int quantity = 0;
    std::string symbol = "";
    double price = 0.0;
public:
    ms_execution(int quantity, const std::string &symbol, double price);

    int getQuantity() const;

    void setQuantity(int quantity);

    const std::string &getSymbol() const;

    void setSymbol(const std::string &symbol);

    double getPrice() const;

    void setPrice(double price);
};


#endif //BRIMUS_MS_EXECUTION_H
