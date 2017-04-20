//
// Created by Behrooz Karjoo on 4/16/17.
//

#ifndef BRIMUS_STOCK_H
#define BRIMUS_STOCK_H

#include "stdafx.h"
#include "cap_msg_field.h"
#include "stock_field.h"
#include "cap_message.h"

enum class cap_file_type {
    FULL,
    SUMMARY
};

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
    boost::gregorian::date dt{1970,01,01};
    std::string last_timestamp;
    int precision = 4;
    void register_field(cap_msg_field *pField);
    size set_size(const std::string&);
    double set_price(const std::string&);
    cap_file_type capType = cap_file_type::SUMMARY;
    // tell the observer packet time, symbol, field, value as double
    boost::signals2::signal<void(const stock&, stock_field)> observers;
public:
    // when connecting, remember to save the connection object and disconnect or add to scoped connection
    boost::signals2::connection add_observer(
            std::function<void(const stock&, stock_field)>);
    void tick_update(std::unique_ptr<cap_message>);
    void tick_update(const cap_message&);
    void time_update(boost::posix_time::ptime _packetTime);
    // getters
    const std::string &Symbol() const;
    price Last() const;
    price Ask() const;
    price Bid() const;
    price Open() const;
    size LastSize() const;
    size AskSize() const;
    size BidSize() const;
    const ptime &Time() const;
    // constructor
    stock(const std::string &symbol);
    stock(){};
    void setSymbol(const std::string& symb) { symbol = symb; }
    const ptime &to_boost_ptime(const std::string& timestamp) const;
    void set_precision(const std::string &basic_string);
    cap_file_type getCapType() const;
    void setCapType(cap_file_type capType);
    const boost::gregorian::date &getDt() const;
    void setDt(const boost::gregorian::date &dt);
};


#endif //BRIMUS_STOCK_H
