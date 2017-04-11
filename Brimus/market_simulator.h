//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_MARKET_SIMULATOR_H
#define BRIMUS_MARKET_SIMULATOR_H

#include "stdafx.h"
#include "order.h"
#include "IOrderSender.h"
#include "ms_order_collection.h"

class instrument;

class market_simulator {
    ms_order_collection open_orders;
    ms_order_collection closed_orders;
    std::map<order*,IOrderSender*> orders;
    std::map<std::string,std::shared_ptr<instrument> > instruments;
    void check_for_fill(const std::string &symbol);

    market_simulator() {}
    ~market_simulator() {}
public:
    market_simulator(market_simulator const&) = delete;
    void operator=(market_simulator const&) = delete;
    static market_simulator& get_instance() { static market_simulator ms; return ms; }

    void add_instrument(std::shared_ptr<instrument>);

    std::string ping() { return "Connected."; }
    std::string ping(std::string);
    void send_order(int qty, std::string symbol, double price, IOrderSender* sender);
    // called by notifier when an instrument is updated


    std::string send_order(int qty, std::string symbol,
                           double price,
                           std::function<void(int,std::string,double,std::string)>);
    std::string send_order(int qty, std::string symbol,double price);
    void cancel_order(std::string id);
    void cancel_order(std::string id,std::function<void(std::string)>);
    std::string cancel_replace_order(std::string id, int qty, std::string symbol,double price,
                                     std::function<void(std::string,int,std::string,double,std::string)>);

    int closed_orders_size() const { return closed_orders.size(); }
    int open_orders_size() const { return open_orders.size(); }

    void notify(std::string symbol);
};


#endif //BRIMUS_MARKET_SIMULATOR_H