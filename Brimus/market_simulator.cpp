//
// Created by b.karjoo on 3/23/2017.
//

#include "market_simulator.h"
#include "instrument.h"

std::shared_ptr<market_simulator> market_simulator::instance = 0;

std::shared_ptr<market_simulator> market_simulator::market() {
    if (!instance) {
        instance = std::make_shared<market_simulator>();
    }
    return instance;
}

void market_simulator::add_instrument(std::shared_ptr<instrument> i) {
    instruments[i->getSymbol()] = i;
}

std::string market_simulator::ping(std::string s) {
    return std::to_string(instruments[s]->getLast_price());
}

void market_simulator::send_order(int qty, std::string symbol, double price, order_sender *sender) {
    order* optr = new order();
    optr->price = price;
    optr->symbol = symbol;
    optr->quantity = qty;
    if (!check_for_fill(optr,sender))
        orders[optr] = sender;
    else
        delete optr;
}

bool market_simulator::check_for_fill(order * o, order_sender* s) {
    if (o->quantity > 0) {
        // it's a buy, check the offer
        // if order price is greater than or equal to the offer fill it
        if (o->price >= instruments[o->symbol]->getAsk_price()) {
            s->on_execution(o->quantity,o->symbol,instruments[o->symbol]->getAsk_price());
        }
        return true;
    } else if (o->quantity < 0) {
        // it's a sell, check the bid
        if (o->price <= instruments[o->symbol]->getBid_price()) {
            s->on_execution(o->quantity,o->symbol,instruments[o->symbol]->getBid_price());
        }
        return true;
    }
    return false;
}

void market_simulator::notify(std::string symbol) {
    for (auto& a : orders) {
        if (a.first->symbol == symbol) {
            if (check_for_fill(a.first,a.second)) {
                delete a.first; // delete the order, leave sender alone
                orders.erase(a.first); // erase the pointers
            }
        }
    }
}




