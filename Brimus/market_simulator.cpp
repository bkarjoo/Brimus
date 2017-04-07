//
// Created by b.karjoo on 3/23/2017.
//

#include "market_simulator.h"
#include "instrument.h"




void market_simulator::add_instrument(std::shared_ptr<instrument> i) {
    instruments[i->getSymbol()] = i;
}

std::string market_simulator::ping(std::string s) {
    return std::to_string(instruments[s]->getLast_price());
}

void market_simulator::send_order(int qty, std::string symbol, double price, IOrderSender* sender) {

    order* optr = new order(qty,symbol,price);
    orders[optr] = sender;
    check_for_fill();
}

void market_simulator::check_for_fill() {
    for (auto it = orders.begin(); it != orders.end();) {
        bool erase = false;
        if (it->first->getQuantity() > 0) {
            // it's a buy, check the offer
            // if order price is greater than or equal to the offer fill it
            std::cout << it->first->getPrice() << std::endl;
            std::cout << it->first->getSymbol() << std::endl;
            std::cout << it->first->getExecuted_qty() << std::endl;
            std::cout << it->first->getQuantity() << std::endl;
            std::cout << instruments[it->first->getSymbol()]->getAsk_price() << std::endl;
            if (it->first->getPrice() >= instruments[it->first->getSymbol()]->getAsk_price()) {
                it->second->on_execution(it->first->getQuantity(), it->first->getSymbol(), instruments[it->first->getSymbol()]->getAsk_price(), it->first->getQuantity());
                delete it->first;
                erase = true;
            }
        } else if (it->first->getQuantity() < 0) {
            // it's a sell, check the bid
            if (it->first->getPrice() <= instruments[it->first->getSymbol()]->getBid_price()) {
                it->second->on_execution(it->first->getQuantity(), it->first->getSymbol(), instruments[it->first->getSymbol()]->getBid_price(), it->first->getQuantity());
                delete it->first;
                erase = true;
            }
        }
        if (erase) it = orders.erase(it); else it++;
    }

}

void market_simulator::notify(std::string symbol) {
    check_for_fill();
}





