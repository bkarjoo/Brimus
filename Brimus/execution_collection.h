//
// Created by b.karjoo on 4/10/2017.
//

#ifndef BRIMUS_EXECUTION_COLLECTION_H
#define BRIMUS_EXECUTION_COLLECTION_H

#include "stdafx.h"
#include "execution.h"

class execution_collection {
    typedef std::unique_ptr<execution> exec_ptr;
    typedef std::vector<exec_ptr> exec_ptr_vector;
    exec_ptr_vector executions;
public:
    void add_execution(exec_ptr);
    void add_execution(int exec_qty, std::string symbol, double price);
    // can't remove an execution
    double last_fill_price(const std::string &) const;
    double last_buy_fill_price(const std::string &) const;
    double last_sell_fill_price(const std::string &) const;
    int execution_collection_size() const;
    double sum_money_flow() const;
    double sum_money_flow(std::string symbol) const;
};


#endif //BRIMUS_EXECUTION_COLLECTION_H
