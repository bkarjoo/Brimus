//
// Created by b.karjoo on 3/24/2017.
//

#ifndef BRIMUS_STRATEGY_ART_H
#define BRIMUS_STRATEGY_ART_H

#include "stdafx.h"
#include "strategy.h"
#include "bar_series.h"

class strategy_art : public strategy {
    std::string endOfDayExitTime = "155959";
    std::map<std::string, std::shared_ptr<bar_series> > FiveMinute;
public:
    strategy_art(std::shared_ptr<launch_rules> lr,
        std::shared_ptr<symbol_basket> sb) :
        strategy(lr,sb) {}
    void notify(std::string);
//    void add_instrument(std::shared_ptr<instrument>);
    bool entryConditions(std::string);
    void placeEntryOrders(std::string);
    bool exitConditions(std::string);
    void placeExitOrders(std::string);
    std::function<void(std::string)> get_on_new_bar_callback();

};


#endif //BRIMUS_STRATEGY_ART_H
