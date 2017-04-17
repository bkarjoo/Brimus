//
// Created by b.karjoo on 4/11/2017.
//

#ifndef BRIMUS_MS_ORDER_COLLECTION_H
#define BRIMUS_MS_ORDER_COLLECTION_H
#include "stdafx.h"
#include "ms_order.h"

class ms_order_collection {


public:
    typedef std::unique_ptr<ms_order> order_ptr;
    typedef std::vector<order_ptr> collection_type;
    void add_order(std::unique_ptr<ms_order> order);
    order_ptr remove_order(const std::string& id);
    const std::unique_ptr<ms_order>& get_order(const std::string& id);
    int size() const;
    // looped over by market simulator to check against quotes
    const collection_type& get_orders() { return orders; }
private:
    collection_type orders;

};


#endif //BRIMUS_MS_ORDER_COLLECTION_H
