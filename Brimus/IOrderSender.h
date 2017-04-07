//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_ORDER_SENDER_H
#define BRIMUS_ORDER_SENDER_H

#include <string>
class IOrderSender {
public:
    virtual void on_execution(int quanity, std::string symbol, double price, int orig_qty) = 0;
};


#endif //BRIMUS_ORDER_SENDER_H
