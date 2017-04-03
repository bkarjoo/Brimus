//
// Created by b.karjoo on 3/28/2017.
//

#ifndef BRIMUS_BASKET_H
#define BRIMUS_BASKET_H

#include <iostream>
#include <memory>
#include "instrument.h"
#include "strategy_basket.h"
#include "symbol_basket.h"

/*
 * global_basket is shared among all classes that need it
 */
class global_basket {
    std::map<std::string,std::vector<std::function<void(std::string)>>> observers;
    std::map<std::string,std::shared_ptr<instrument>> instruments;
    global_basket() {}
    ~global_basket() { }
public:
    global_basket(global_basket const&) = delete;
    void operator=(global_basket const&) = delete;
    static global_basket& get_instance()
    {
        static global_basket gb;
        return gb;
    }

    double LastPrice(std::string symbol) {
        return instruments[symbol]->getLast_price();
    }

    std::shared_ptr<instrument> add_instrument(std::string symbol);
    void add_basket(const std::shared_ptr<symbol_basket>, std::function<void(std::string)>);
    void add_observer(std::string symbol, std::function<void(std::string)> callback);

    //std::function<void(std::string)> get_callback();
    std::function<void(instrument& , const std::string&)> get_callback();
};


#endif //BRIMUS_BASKET_H
