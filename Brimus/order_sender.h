//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_ORDER_SENDER_H
#define BRIMUS_ORDER_SENDER_H

#include <string>
class order_sender {
public:
    virtual void on_execution(int quanity, std::string symbol, double price) = 0;
};


#endif //BRIMUS_ORDER_SENDER_H
