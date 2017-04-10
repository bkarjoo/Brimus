//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_STRATEGY_BASKET_H
#define BRIMUS_STRATEGY_BASKET_H

#include "stdafx.h"
#include "global_basket.h"
#include "live_data_server.h"
#include "pcap_file.h"
#include "pcap_file_server.h"
#include "strategy.h"
#include "symbol_basket.h"





/*
 *  sets up the strategies by binding them to get notifications for price
 *  and orders, and then runs.
 */
class strategy_basket {
    std::vector<std::shared_ptr<strategy>> strategies;
public:
    void add_strategy(const std::shared_ptr<strategy> strat);
    void run_live();
    void run_backtests();
};


#endif //BRIMUS_STRATEGY_BASKET_H
