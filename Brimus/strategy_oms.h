//
// Created by b.karjoo on 3/29/2017.
//

#ifndef BRIMUS_STRATEGY_OMS_H
#define BRIMUS_STRATEGY_OMS_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "order.h"
#include "execution.h"
#include "IOrderSender.h"
#include "order_collection.h"
#include "position.h"
#include "position_collection.h"

class strategy_oms :
        public IOrderSender {
    // TODO : use a persistent database for orders to protect against sys crash

    std::vector<std::shared_ptr<order>> oo;
    order_collection open_orders;
    order_collection closed_orders;
    position_collection positions;
    std::map<std::string, std::vector<std::shared_ptr<execution> > > executions;
public:
    bool has_position(std::string symbol);
    bool has_open_orders(std::string symbol);
    bool has_open_buy_orders(std::string symbol);
    bool has_open_sell_orders(std::string symbol);
    int get_position(std::string symbol);
    double sum_money_flow(const std::vector<std::string>&);
    double sum_money_flow(std::string);
    double open_position_value();
    double open_position_value(std::string);
    double pandl();
    double pandl(std::string);
    void submit(int qty, std::string symbol, double price);
    void on_execution(int quanity, std::string symbol, double price, int orig_qty) override;
    double last_execution_price(std::string);

};


#endif //BRIMUS_STRATEGY_OMS_H
