//
// Created by b.karjoo on 5/3/2017.
//

#ifndef BRIMUS_SIMPLE_TRADE_H
#define BRIMUS_SIMPLE_TRADE_H

#include "stdafx.h"
#include "simple_order.h"
#include "simple_order_collection.h"

class simple_trade {
    simple_order_collection entryOrders;
    simple_order_collection exitOrders;
public:
    // this is the initial state of a trade, an order submited
    simple_trade(std::shared_ptr<simple_order>);

    void add_order(std::shared_ptr<simple_order>);

    double average_entry_price();

    double average_exit_price();

    boost::optional<boost::posix_time::ptime> first_entry_time();

    boost::optional<boost::posix_time::ptime> first_exit_time();

    boost::optional<boost::posix_time::ptime> last_entry_time();

    boost::optional<boost::posix_time::ptime> last_exit_time();

    int entry_execution_quantity();

    int exit_execution_quantity();

    int total_executed_quantity();

    // a trade is closed when the entry and exit match
    bool is_closed();

    bool is_open();

    int closed_quantity();

    int open_quantity();

    std::string getSymbol();

    std::string getSide();

    double entry_dollar_value();

    double exit_dollar_value();

    double dollar_difference();

    double cents_per_share();

    double exposure();

    double open_profit_or_loss(double currentPrice);

    double closed_profit_or_loss();



    std::string csv_stats();

};


#endif //BRIMUS_SIMPLE_TRADE_H
