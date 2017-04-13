//
// Created by b.karjoo on 3/23/2017.
//

#include "market_simulator.h"
#include "instrument.h"
#include "global_basket.h"


using namespace std;

//void market_simulator::add_instrument(shared_ptr<instrument> &i) {
//    global_basket& gb = global_basket::get_instance();
//    if (gb.get_instrument_ptr(i->getSymbol()) == nullptr) {
//        i = global_basket::get_instance().add_instrument(i->getSymbol());
//    } else
//        i = gb.get_instrument_ptr(i->getSymbol());
////    instruments[i->getSymbol()] = i;
//}

std::string market_simulator::ping(std::string s) {
    //auto instrPtr = instruments[s];
    return std::to_string(global_basket::get_instance().LastPrice(s));
//    if (instrPtr)
//        return std::to_string(instruments[s]->getLast_price());
//    else
//        return "Instrument not found.";
}

//void market_simulator::send_order(int qty, std::string symbol, double price, IOrderSender* sender) {
//
//    order* optr = new order(qty,symbol,price);
//    orders[optr] = sender;
//    check_for_fill(symbol);
//}

void market_simulator::check_for_fill(const std::string &symbol) {
    auto& orders = open_orders.get_orders();

    for (auto& it : orders) {
        //auto instr = instruments[it->getSymbol()];
        global_basket& gb = global_basket::get_instance();
        double bid = gb.BidPrice(symbol);
        double ask = gb.AskPrice(symbol);
        if (it->getSymbol() == symbol) {
            // check for fill - const pointer
            int order_qty = it->getQuantity();
            double order_price = it->getPrice();
            if (bid != 0 && ask != 0) {

                if ((order_qty > 0 && order_price >= ask) ||
                    (order_qty < 0 && order_price <= bid)) {
                    // record fill in order
                    int execQty = 0;
                    order_qty > 0
                        ? execQty = min(100, it->remain_qty())
                        : execQty = max(-100, it->remain_qty());
                    it->setQuantity(execQty);
                    double execPrice = it->getQuantity() > 0 ? ask : bid;
                    it->add_execution(execQty, execPrice);
                    // report fill
                    auto f = it->getCallback();
                    if (f) {
                        f(execQty,
                          execPrice,
                          it->getId()
                        );
                    }
                    // request removal from collection
                    closed_orders.add_order(open_orders.remove_order(it->getId()));
                }
            }
        }
    }
}

void market_simulator::notify(std::string symbol) {
    check_for_fill(symbol);
}

std::string market_simulator::send_order(int qty, std::string symbol, double price,
                                         std::function<void(int&, double&, const std::string&)> callback) {
    order* optr = new order(qty,symbol,price);
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid1 = generator();
    string id =  boost::lexical_cast<string>(uuid1);
    auto orderPtr = make_unique<ms_order>(qty,symbol,price,id);
    orderPtr->setCallback(callback);
    open_orders.add_order(move(orderPtr));
    check_for_fill(symbol);
    return id;
}

std::string market_simulator::send_order(int qty, std::string symbol, double price) {
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid1 = generator();
    string id =  boost::lexical_cast<string>(uuid1);
    auto orderPtr = make_unique<ms_order>(qty,symbol,price,id);
    open_orders.add_order(move(orderPtr));
    check_for_fill(symbol);
    return id;
}

void market_simulator::cancel_order(std::string id) {
    // search open orders for the id
    auto& orders = open_orders.get_orders();
    auto orderToCancel = open_orders.remove_order(id);
    if (orderToCancel)
        closed_orders.add_order(move(orderToCancel));
}

void market_simulator::cancel_order(std::string id, std::function<void(std::string)> callback) {
    auto& orders = open_orders.get_orders();
    auto orderToCancel = open_orders.remove_order(id);
    if (orderToCancel) {
        closed_orders.add_order(move(orderToCancel));
        callback(id);
    }
}

std::string market_simulator::cancel_replace_order(std::string id, double new_price) {
    auto& orders = open_orders.get_orders();
    auto orderToCancel = open_orders.remove_order(id);
    if (orderToCancel) {
        auto callback = orderToCancel->getCallback();
        auto qty = orderToCancel->getQuantity();
        auto symbol = orderToCancel->getSymbol();
        closed_orders.add_order(move(orderToCancel));
        if (callback) {
            return send_order(qty, symbol, new_price, callback);
        } else {
            return send_order(qty, symbol, new_price);
        }
    } else
        return "";
}

std::string market_simulator::cancel_replace_order(std::string id, int new_qty, double new_price) {
    auto& orders = open_orders.get_orders();
    auto orderToCancel = open_orders.remove_order(id);
    if (orderToCancel) {
        auto callback = orderToCancel->getCallback();
        auto symbol = orderToCancel->getSymbol();
        closed_orders.add_order(move(orderToCancel));
        if (callback) {
            return send_order(new_qty, symbol, new_price, callback);
        } else {
            return send_order(new_qty, symbol, new_price);
        }
    } else
        return "";


}




