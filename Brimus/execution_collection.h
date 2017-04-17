//
// Created by b.karjoo on 4/10/2017.
//

#ifndef BRIMUS_EXECUTION_COLLECTION_H
#define BRIMUS_EXECUTION_COLLECTION_H

#include "stdafx.h"
#include "execution.h"

class execution_collection {
    std::vector<execution> executions;
public:
    void add_execution(const execution&);
    void add_execution(int exec_qty, std::string symbol, double price);
    void add_execution(int execQty, std::string symbol, double price, std::string id);
    // can't remove an execution
    double last_fill_price(const std::string &) const;
    double last_buy_fill_price(const std::string &) const;
    double last_sell_fill_price(const std::string &) const;
    int execution_collection_size() const;
    double sum_money_flow() const;
    double sum_money_flow(std::string symbol) const;
    int sum_executions(const std::string& id) const;
};


#endif //BRIMUS_EXECUTION_COLLECTION_H
