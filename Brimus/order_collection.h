//
// Created by b.karjoo on 4/6/2017.
//

#ifndef BRIMUS_ORDER_COLLECTION_H
#define BRIMUS_ORDER_COLLECTION_H

#include "stdafx.h"
#include "order.h"

class order_collection {
    typedef std::unique_ptr<order> ord_ptr;
    typedef std::vector<ord_ptr> ord_ptr_vec;

    ord_ptr_vec orders;
    // ord_ptr null_unique;
public:
    // void add_order(ord_ptr);
    boost::optional<order &> add_order(int qty, std::string symbol, double price);
    boost::optional<order &> add_order(int qty, const std::string &symbol, double price, order_type oType);
    boost::optional<order &> add_order();
    void pass_order(ord_ptr);
    boost::optional<order &> find_order(std::string id);
    boost::optional<order&> boost_find_order(std::string id);
    boost::optional<order &> find_order(int qty, std::string symbol, double price);
    void remove_order(int qty, std::string symbol, double price);
    ord_ptr fetch_remove_order(int qty, std::string symbol, double price);
    ord_ptr fetch_remove_order(std::string id);
    bool has_open_order(const std::string&) const;
    bool has_open_buy_order(const std::string&) const;
    bool has_open_sell_order(const std::string&) const;
    int size() const { return orders.size(); }
    order* findOrder(std::string id);
    boost::optional<order &> find_first_buy_order(const std::string &symbol) const;
    boost::optional<order &> find_first_buy_order(const std::string &symbol, order_type oType) const;
    boost::optional<order &> find_first_sell_order(const std::string &symbol) const;
    boost::optional<order &> find_first_sell_order(const std::string &symbol, order_type oType) const;

};


#endif //BRIMUS_ORDER_COLLECTION_H
