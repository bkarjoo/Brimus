//
// Created by b.karjoo on 5/3/2017.
//

#ifndef BRIMUS_SIMPLE_ORDER_H
#define BRIMUS_SIMPLE_ORDER_H

#include <ostream>
#include "stdafx.h"
#include "simple_execution.h"

class simple_order {
    int originalQuantity = 0;
    std::string symbol = "";
    double limitPrice = 0.0;
    boost::posix_time::ptime orderPlacementTime;
    std::vector<std::shared_ptr<simple_execution>> executions;
public:

    simple_order(int originalQuantity, const std::string &symbol, double limitPrice);

    void add_execution(std::shared_ptr<simple_execution>);

    boost::optional<boost::posix_time::ptime> first_execution_time();

    boost::optional<boost::posix_time::ptime> last_execution_time();

    bool is_filled();

    double average_execution_price();

    int executed_quantity();

    int leaves_quantity();

    double total_dollar_value();

    int getOriginalQuantity() const;

    const std::string &getSymbol() const;

    double getLimitPrice() const;

    const boost::posix_time::ptime &getOrderPlacementTime() const;

    void setOrderPlacementTime(const boost::posix_time::ptime &orderPlacementTime);

    friend std::ostream &operator<<(std::ostream &os, const simple_order &order);
};


#endif //BRIMUS_SIMPLE_ORDER_H
