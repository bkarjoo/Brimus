//
// Created by b.karjoo on 5/3/2017.
//

#ifndef BRIMUS_SIMPLE_ORDER_COLLECTION_H
#define BRIMUS_SIMPLE_ORDER_COLLECTION_H

#include "stdafx.h"
#include "simple_order.h"

class simple_order_collection {
    typedef std::shared_ptr<simple_order> order_ptr;
    typedef std::vector<order_ptr> order_vector;
    order_vector orders;
public:
    void add_order(order_ptr);

    double average_price();

    int execution_quantity();

    boost::optional<boost::posix_time::ptime> first_execution_time();

    boost::optional<boost::posix_time::ptime> last_execution_time();

    boost::optional<std::string> get_symbol();

    boost::optional<std::string> get_side();

    double dollar_value();


};


#endif //BRIMUS_SIMPLE_ORDER_COLLECTION_H
