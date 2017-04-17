//
// Created by b.karjoo on 4/6/2017.
//

#include "order_collection.h"

using namespace std;

bool order_collection::has_open_order(const std::string& symbol) const{
    auto it = std::find_if(orders.begin(),orders.end(),
        [&symbol](const order_collection::ord_ptr & sptr) {
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
                           [&symbol](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol
                               && sptr->getQuantity() < 0;

                           });
    return it != orders.end();
}

bool order_collection::has_open_buy_order(const std::string &symbol) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&symbol](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol
                               && sptr->getQuantity() > 0;
                           });
    return it != orders.end();
}

boost::optional<order &> order_collection::find_order(int qty, std::string symbol, double price) {
    auto it = std::find_if(orders.begin(),orders.end(),
                             [&](const order_collection::ord_ptr & sptr) {
                                 return
                                         sptr->getQuantity() == qty &&
                                         sptr->getSymbol() == symbol &&
                                         abs(sptr->getPrice() - price) < .000001;
                             });

    if (it == orders.end()) return {};
    return **it;
}

order_collection::ord_ptr order_collection::fetch_remove_order(int qty, std::string symbol, double price) {
    for ( auto it = orders.begin(); it != orders.end(); ) {
        if ( (*it)->getQuantity() == qty
             && (*it)->getSymbol() == symbol
             && (*it)->getPrice() == price) {
            ord_ptr ptr = move(*it);
            orders.erase(it);
            return move(ptr);
        } else {
            ++it;
        }
    }
    return {};
}

boost::optional<order &> order_collection::find_order(std::string id) {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getId() == id;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

order_collection::ord_ptr order_collection::fetch_remove_order(std::string id) {
    for ( auto it = orders.begin(); it != orders.end(); ) {
        if ( (*it)->getId() == id ) {
            ord_ptr ptr = move(*it);
            orders.erase(it);
            return move(ptr);
        } else {
            ++it;
        }
    }
    return {};
}

boost::optional<order &> order_collection::add_order(int qty, std::string symbol, double price) {
    auto ord = make_unique<order>(qty,symbol,price);
    orders.push_back(move(ord));
    return *ord;
}

boost::optional<order &>
order_collection::add_order(int qty, const std::string &symbol, double price, order_type oType) {
    auto ord = make_unique<order>(qty,symbol,price,oType);
    orders.push_back(move(ord));
    return *ord;
}

void order_collection::pass_order(ord_ptr ord) {
    orders.push_back(move(ord));
}

boost::optional<order &> order_collection::find_first_buy_order(const std::string &symbol) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol && sptr->getQuantity() > 0;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

boost::optional<order &> order_collection::find_first_sell_order(const std::string &symbol) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol && sptr->getQuantity() < 0;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

boost::optional<order &> order_collection::find_first_buy_order(const std::string &symbol, order_type oType) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol
                                      && sptr->getQuantity() > 0
                                       && sptr->getOType() == oType;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

boost::optional<order &> order_collection::find_first_sell_order(const std::string &symbol, order_type oType) const {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getSymbol() == symbol
                                      && sptr->getQuantity() < 0
                                       && sptr->getOType() == oType;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

boost::optional<order &> order_collection::boost_find_order(std::string id) {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getId() == id;
                           });

    if (it == orders.end())
        return {};
    return **it;
}

order *order_collection::findOrder(std::string id) {
    auto it = std::find_if(orders.begin(),orders.end(),
                           [&](const order_collection::ord_ptr & sptr) {
                               return sptr->getId() == id;
                           });

    if (it == orders.end())
        return nullptr;
    return it->get();
}







//boost::optional<boost::reference_wrapper<order>> order_collection::find_order(const std::string &id) const {
//    auto it = std::find_if(orders.begin(),orders.end(),
//                           [&](const order_collection::ord_ptr & sptr) {
//                               return sptr->getId() == id;
//                           });
//
//    if (it == orders.end())
//        return {};
//    return **it;
//}

// const order *& order_collection::find_order(const std::string &id) const {
//    auto it = std::find_if(orders.begin(),orders.end(),
//                           [&](const order_collection::ord_ptr & sptr) {
//                               return sptr->getId() == id;
//                           });
//
//    if (it == orders.end())
//        return nullptr;
//    return it->get();
//}




