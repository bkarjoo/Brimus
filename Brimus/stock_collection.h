//
// Created by b.karjoo on 4/17/2017.
//

#ifndef BRIMUS_STOCK_COLLECTION_H
#define BRIMUS_STOCK_COLLECTION_H

#include "stdafx.h"
#include "IMessageReceiver.h"
#include "stock.h"
#include "symbol_basket.h"

class stock_collection {
    typedef boost::posix_time::ptime ptime;
    std::map<std::string,stock> stocks;
    stock_collection() {}
    ~stock_collection() {}
public:
    stock_collection(stock_collection const&) = delete;
    void operator=(stock_collection const&) = delete;
    static stock_collection& get_instance() { static stock_collection sc; return sc; }
    stock& add_stock(std::string);
    void add_basket(const symbol_basket&,
                    std::function<void(const ptime&, const std::string&, stock_field, double)>);
    void on_message(const st_message &message);
    bool has_instrument(const std::string &string);
};


#endif //BRIMUS_STOCK_COLLECTION_H
