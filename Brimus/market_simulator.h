//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_MARKET_SIMULATOR_H
#define BRIMUS_MARKET_SIMULATOR_H

#include <map>
#include <memory>
#include "order.h"
#include "order_sender.h"

class instrument;

class market_simulator {

    std::map<order*,order_sender*> orders;
    static std::shared_ptr<market_simulator> instance;
    std::map<std::string,std::shared_ptr<instrument> > instruments;
    bool check_for_fill(order*,order_sender*);
public:
    static std::shared_ptr<market_simulator> market();
    std::string ping() { return "Connected."; }
    void add_instrument(std::shared_ptr<instrument>);
    std::string ping(std::string);
    void send_order(int qty, std::string symbol, double price, order_sender* sender);
    // called by notifier when an instrument is updated
    void notify(std::string symbol);
};


#endif //BRIMUS_MARKET_SIMULATOR_H