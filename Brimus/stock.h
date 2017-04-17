//
// Created by Behrooz Karjoo on 4/16/17.
//

#ifndef BRIMUS_STOCK_H
#define BRIMUS_STOCK_H

#include "stdafx.h"
#include "st_field.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "stock_field.h"
#include "st_message.h"
#include <boost/signals2.hpp>


class stock {
    typedef boost::posix_time::ptime ptime;
    typedef double price;
    typedef int size;
    std::string symbol;
    price last = 0.0;
    price ask = 0.0;
    price bid = 0.0;
    price open = 0.0;
    size lastSize = 0;
    size askSize = 0;
    size bidSize = 0;
    ptime packetTime;
    void register_field(st_field *pField);
    size set_size(const std::string&);
    double set_price(const std::string&);
    // tell the observer packet time, symbol, field, value as double
    boost::signals2::signal<void(const ptime&, const std::string&, stock_field, double)> observers;
public:
    // when connecting, remember to save the connection object and disconnect or add to scoped connection
    boost::signals2::connection add_observer(std::function<void(const ptime&, const std::string&, stock_field, double)>);
    void tick_update(std::unique_ptr<st_message>);
    void time_update(boost::posix_time::ptime _packetTime);
    // getters
    const std::string &getSymbol() const;
    price getLast() const;
    price getAsk() const;
    price getBid() const;
    price getOpen() const;
    size getLastSize() const;
    size getAskSize() const;
    size getBidSize() const;
    const ptime &getPacketTime() const;
    // constructor
    stock(const std::string &symbol);
};


#endif //BRIMUS_STOCK_H
