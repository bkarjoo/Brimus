//
// Created by b.karjoo on 4/11/2017.
//

#ifndef BRIMUS_MS_ORDER_H
#define BRIMUS_MS_ORDER_H
#include "stdafx.h"
#include "ms_execution.h"
#include "ms_execution_collection.h"

class ms_order {
    int quantity = 0;
    std::string symbol = "";
    double price = 0;
    std::string id = "";
    ms_execution_collection executions;
    std::function<void(int fillQty,
                       std::string symbol,
                       double fillPrice,
                       std::string orderId)> callback = nullptr;

public:


    ms_order(int quantity,
             const std::string &symbol,
             double price,
             const std::string &id,
             const std::function<void(int, std::string, double, std::string)> &callback);

    ms_order(int quantity, const std::string &symbol, double price, const std::string &id);

    int getQuantity() const;

    void setQuantity(int quantity);

    const std::string &getSymbol() const;

    void setSymbol(const std::string &symbol);

    double getPrice() const;

    void setPrice(double price);

    const std::string &getId() const;

    void setId(const std::string &id);

    const std::function<void(int, std::string, double, std::string)> &getCallback() const;

    void setCallback(const std::function<void(int, std::string, double, std::string)> &callback);

    void add_execution(int qty, double price);

    int execution_qty();

    bool is_filled();

    int remain_qty();
};


#endif //BRIMUS_MS_ORDER_H
