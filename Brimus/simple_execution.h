//
// Created by b.karjoo on 5/3/2017.
//

#ifndef BRIMUS_SIMPLE_EXECUTION_H
#define BRIMUS_SIMPLE_EXECUTION_H

#include <ostream>
#include "stdafx.h"

class simple_execution {
    int quantity = 0;
    std::string symbol = "";
    double fillPrice = 0.0;
    boost::posix_time::ptime executionTime;
public:
    simple_execution(int quantity, const std::string &symbol, double fillPrice,
                     const boost::posix_time::ptime &executionTime);

    double dollar_value();

    int getQuantity() const;

    const std::string &getSymbol() const;

    double getFillPrice() const;

    const boost::posix_time::ptime &getExecutionTime() const;

    friend std::ostream &operator<<(std::ostream &os, const simple_execution &execution);

};


#endif //BRIMUS_SIMPLE_EXECUTION_H
