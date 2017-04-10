//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_MARKET_SIMULATOR_H
#define BRIMUS_MARKET_SIMULATOR_H

#include "stdafx.h"
#include "order.h"
#include "IOrderSender.h"

class instrument;

class market_simulator {
    std::map<order*,IOrderSender*> orders;
    std::map<std::string,std::shared_ptr<instrument> > instruments;
    void check_for_fill();
    market_simulator() {}
    ~market_simulator() {}
public:
    market_simulator(market_simulator const&) = delete;
    void operator=(market_simulator const&) = delete;
    static market_simulator& get_instance() { static market_simulator ms; return ms; }
    std::string ping() { return "Connected."; }
    void add_instrument(std::shared_ptr<instrument>);
    std::string ping(std::string);
    void send_order(int qty, std::string symbol, double price, IOrderSender* sender);
    // called by notifier when an instrument is updated
    void notify(std::string symbol);
};


#endif //BRIMUS_MARKET_SIMULATOR_H