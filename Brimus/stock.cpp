//
// Created by Behrooz Karjoo on 4/16/17.
//

#include "stock.h"

using namespace boost;
using namespace boost::signals2;

stock::stock(const std::string &symbol) : symbol(symbol) {}

const std::string &stock::Symbol() const {
    return symbol;
}

stock::price stock::Last() const {
    return last;
}

stock::price stock::Ask() const {
    return ask;
}

stock::price stock::Bid() const {
    return bid;
}

stock::price stock::Open() const {
    return open;
}

stock::size stock::LastSize() const {
    return lastSize;
}

stock::size stock::AskSize() const {
    return askSize;
}

stock::size stock::BidSize() const {
    return bidSize;
}

const stock::ptime &stock::Time() const {
    return packetTime;
}

boost::signals2::connection stock::add_observer(
        std::function<void(const stock &, stock_field)> observer) {
    return observers.connect(observer);
}

void stock::tick_update(std::unique_ptr<cap_message> msg) {
    for (auto a : msg->get_fields())
        register_field(a);
}

void stock::tick_update(const cap_message &msg) {
    for (auto a : msg.get_fields())
        register_field(a);
}

void stock::register_field(cap_msg_field *pField) {
    switch (pField->field_code) {
        case 'a':
            ask = set_price(pField->field_value);
            observers(*this, stock_field::ASK);
            break;
        case 'b':
            bid = set_price(pField->field_value);
            observers(*this, stock_field::BID);
            break;
        case 'j':
            bidSize = set_size(pField->field_value);
            observers(*this, stock_field::BID_SIZE);
            break;
        case 'k':
            askSize = set_size(pField->field_value);
            observers(*this, stock_field::ASK_SIZE);
            break;
        case 'o':
            open = set_price(pField->field_value);
            observers(*this, stock_field::OPEN);
            break;
        case 't':
            last = set_price(pField->field_value);
            observers(*this, stock_field::LAST);
            break;
    }
}

stock::size stock::set_size(const std::string & vol) {
    try {
        return stoi(vol);
    } catch (...) {
        return 0;
    }
}

double stock::set_price(const std::string & prc) {
    try {
        return stod(prc);
    } catch (...) {
        return 0;
    }
}

void stock::time_update(boost::posix_time::ptime _packetTime) {
    packetTime = _packetTime;
}


