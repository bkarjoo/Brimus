//
// Created by b.karjoo on 4/17/2017.
//

#ifndef BRIMUS_STOCK_COLLECTION_H
#define BRIMUS_STOCK_COLLECTION_H

#include "stdafx.h"
#include "IMessageReceiver.h"
#include "stock.h"
#include "strategy_symbol_basket.h"

class stock_collection {
    typedef boost::posix_time::ptime ptime;
    typedef std::shared_ptr<stock> stock_ptr;
    typedef std::map<std::string,stock_ptr> stock_map;
    stock_map stocks;
    stock_collection() {}
    ~stock_collection() {}
public:

    stock_collection(stock_collection const&) = delete;
    void operator=(stock_collection const&) = delete;
    static stock_collection& get_instance() { static stock_collection sc; return sc; }
    stock& add_stock(std::string);

    void add_stock(const std::string&,
                   std::function<void(const stock&, stock_field)>);

    // makes caller an observer to the stock
    void add_basket(const strategy_symbol_basket&,
                    std::function<void(const stock&, stock_field)>);
    void on_message(const cap_message &message);
    bool has_instrument(const std::string &string);
    std::shared_ptr<stock> get_stock(const std::string&);
    int size() { return stocks.size(); }
    double AskPrice(const std::string&);
    double BidPrice(const std::string&);
    double LastPrice(const std::string&);
};


#endif //BRIMUS_STOCK_COLLECTION_H
