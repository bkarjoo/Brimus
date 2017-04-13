//
// Created by b.karjoo on 3/29/2017.
//

#ifndef BRIMUS_STRATEGY_OMS_H
#define BRIMUS_STRATEGY_OMS_H

#include "stdafx.h"
#include "order.h"
#include "execution.h"
#include "IOrderSender.h"
#include "order_collection.h"
#include "position.h"
#include "position_collection.h"
#include "execution_collection.h"

class strategy_oms :
        public IOrderSender {
    // TODO : use a persistent database for orders to protect against sys crash (sqlite)
    order_collection open_orders;
    order_collection closed_orders;
    position_collection positions;
    execution_collection executions;
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
    std::string submit(int qty, std::string symbol, double price);
    std::string cancel_replace(int newQty, std::string symbol, double newPrice);
    void on_execution(int quanity, const std::string &symbol, double price, int orig_qty, double orig_price) override;
    double last_execution_price(std::string);
    void on_execution(int execQty, double execPrice, const std::string& orderId);
    int sum_execution_qty(const std::string &id);
};


#endif //BRIMUS_STRATEGY_OMS_H
