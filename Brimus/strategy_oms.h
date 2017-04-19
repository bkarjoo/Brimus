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
    bool has_position(std::string symbol) const;
    bool has_open_orders(std::string symbol) const;
    bool has_open_buy_orders(std::string symbol) const;
    bool has_open_sell_orders(std::string symbol) const;
    int get_position(std::string symbol) const;
    double sum_money_flow(const std::vector<std::string>&) const;
    double sum_money_flow(std::string) const;
    double open_position_value() const;
    double open_position_value(std::string) const;
    double pandl() const;
    double pandl(std::string) const;
    const std::string& submit(int qty, const std::string &symbol, double price);

    void buy_entry(int qty, const std::string& symbol, double price);
    void short_entry(int qty, const std::string& symbol, double price);
    void buy_target(int qty, const std::string& symbol, double price);
    void sell_target(int qty, const std::string& symbol, double price);
    void buy_stop_loss(int qty, const std::string& symbol, double price);
    void sell_stop_loss(int qty, const std::string& symbol, double price);

//    void buy_entry(int qty, const std::string& symbol, double price, int tif_sec);
//    void short_entry(int qty, const std::string& symbol, double price, int tif_sec);
//    void buy_target(int qty, const std::string& symbol, double price, int tif_sec);
//    void sell_target(int qty, const std::string& symbol, double price, int tif_sec);
//    void buy_stop_loss(int qty, const std::string& symbol, double price, int tif_sec);
//    void sell_stop_loss(int qty, const std::string& symbol, double price, int tif_sec);

    void cancel_replace_buy_entry(int newQty, const std::string& symbol, double newPrice);
    void cancel_replace_short_entry(int newQty, const std::string& symbol, double newPrice);
    void cancel_replace_buy_target(int newQty, const std::string& symbol, double newPrice);
    void cancel_replace_sell_target(int newQty, const std::string& symbol, double newPrice);
    void cancel_replace_buy_stop_loss(int newQty, const std::string& symbol, double newPrice);
    void cancel_replace_sell_stop_loss(int newQty, const std::string& symbol, double newPrice);



    void on_execution(int quanity, const std::string &symbol, double price, int orig_qty, double orig_price) override;
    double last_execution_price(std::string) const;
    int sum_execution_qty(const std::string &id) const;

};


#endif //BRIMUS_STRATEGY_OMS_H
