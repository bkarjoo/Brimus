//
// Created by b.karjoo on 3/28/2017.
//

#ifndef BRIMUS_BASKET_H
#define BRIMUS_BASKET_H

#include "stdafx.h"
#include "instrument.h"
#include "strategy_basket.h"
#include "symbol_basket.h"

/*
 * global_basket is static and accessible to all classes which need quotes
 *
 * a collection of instruments updated with each tick.
 */
class global_basket   {
    std::map<std::string,std::vector<std::function<void(std::string)>>> observers;
    std::map<std::string,std::unique_ptr<instrument>> instruments;
    global_basket() {}
    ~global_basket() { }
public:
    global_basket(global_basket const&) = delete;
    void operator=(global_basket const&) = delete;
    static global_basket& get_instance(){static global_basket gb;return gb;}
    double LastPrice(std::string symbol) {return instruments[symbol]->getLast_price();}
    double BidPrice(std::string symbol) {return instruments[symbol]->getBid_price();}
    double AskPrice(std::string symbol) {return instruments[symbol]->getAsk_price();}
    instrument & add_instrument(std::string symbol);
    void add_basket(const std::shared_ptr<symbol_basket>, std::function<void(std::string)>);
    void symbol_observer(std::string symbol, std::function<void(std::string)> symbol_changed_callback);
    boost::optional<instrument&> get_instrument(std::string symbol);

};


#endif //BRIMUS_BASKET_H
