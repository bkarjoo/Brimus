//
// Created by b.karjoo on 4/6/2017.
//

#ifndef BRIMUS_ORDER_COLLECTION_H
#define BRIMUS_ORDER_COLLECTION_H

#include "stdafx.h"
#include "order.h"

class order_collection {
    typedef std::shared_ptr<order> ord_ptr;
    typedef std::vector<std::shared_ptr<order>> ord_ptr_vec;
    ord_ptr_vec orders;
public:
    void add_order(ord_ptr);
    ord_ptr find_order(int qty, std::string symbol, double price);
    void remove_order(int qty, std::string symbol, double price);
    ord_ptr fetch_remove_order(int qty, std::string symbol, double price);
    bool has_open_order(const std::string&) const;
    bool has_open_buy_order(const std::string&) const;
    bool has_open_sell_order(const std::string&) const;
    int size() const { return orders.size(); }
};


#endif //BRIMUS_ORDER_COLLECTION_H
