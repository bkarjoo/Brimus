//
// Created by b.karjoo on 4/6/2017.
//

#include "order_collection.h"

void order_collection::add_order(order_collection::ord_ptr order) {
    orders.push_back(order);
}

bool order_collection::has_open_order(const std::string& symbol) const{
    auto it = std::find_if(orders.begin(),orders.end(),
        [&symbol](std::shared_ptr<order> sptr) {
           return sptr->getSymbol() == symbol;
        });
    return it != orders.end();
}

void order_collection::remove_order(int qty, std::string symbol, double price) {
    for ( auto it = orders.begin(); it != orders.end(); ) {
        if ( (*it)->getQuantity() == qty
                && (*it)->getSymbol() == symbol
                && (*it)->getPrice() == price) {
            it = orders.erase(it);
            return;
        } else {
            ++it;
        }
    }
}

bool order_collection::has_open_sell_order(const std::string &symbol) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&symbol](std::shared_ptr<order> sptr) {
                               return sptr->getSymbol() == symbol
                               && sptr->getQuantity() < 0;

                           });
    return it != orders.end();
}

bool order_collection::has_open_buy_order(const std::string &symbol) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&symbol](std::shared_ptr<order> sptr) {
                               return sptr->getSymbol() == symbol
                               && sptr->getQuantity() > 0;
                           });
    return it != orders.end();
}

order_collection::ord_ptr order_collection::find_order(int qty, std::string symbol, double price) {
    auto it = std::find_if(orders.begin(),orders.end(),
                             [&](std::shared_ptr<order> sptr) {
                                 return
                                         sptr->getQuantity() == qty &&
                                         sptr->getSymbol() == symbol &&
                                         abs(sptr->getPrice() - price) < .000001;
                             });

    return (it != orders.end() ? *it : nullptr);
}

order_collection::ord_ptr order_collection::fetch_remove_order(int qty, std::string symbol, double price) {
    for ( auto it = orders.begin(); it != orders.end(); ) {
        if ( (*it)->getQuantity() == qty
             && (*it)->getSymbol() == symbol
             && (*it)->getPrice() == price) {
            ord_ptr ptr = *it;
            orders.erase(it);
            return ptr;
        } else {
            ++it;
        }
    }
    return nullptr;
}


