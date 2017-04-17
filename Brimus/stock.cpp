//
// Created by Behrooz Karjoo on 4/16/17.
//

#include "stock.h"

using namespace boost;
using namespace boost::signals2;

stock::stock(const std::string &symbol) : symbol(symbol) {}

const std::string &stock::getSymbol() const {
    return symbol;
}

stock::price stock::getLast() const {
    return last;
}

stock::price stock::getAsk() const {
    return ask;
}

stock::price stock::getBid() const {
    return bid;
}

stock::price stock::getOpen() const {
    return open;
}

stock::size stock::getLastSize() const {
    return lastSize;
}

stock::size stock::getAskSize() const {
    return askSize;
}

stock::size stock::getBidSize() const {
    return bidSize;
}

const stock::ptime &stock::getPacketTime() const {
    return packetTime;
}

boost::signals2::connection stock::add_observer(std::function<void(const stock::ptime &, const std::string &, stock_field, double)> observer) {
    return observers.connect(observer);
}

void stock::tick_update(std::unique_ptr<st_message> msg) {
    for (auto a : msg->get_fields())
        register_field(a);
}

void stock::register_field(st_field *pField) {
    switch (pField->field_code) {
        case 'a':
            ask = set_price(pField->field_value);
            observers(packetTime, symbol, stock_field::ASK, ask);
            break;
        case 'b':
            bid = set_price(pField->field_value);
            observers(packetTime, symbol, stock_field::BID, bid);
            break;
        case 'j':
            bidSize = set_size(pField->field_value);
            observers(packetTime, symbol, stock_field::BID_SIZE, bidSize);
            break;
        case 'k':
            askSize = set_size(pField->field_value);
            observers(packetTime, symbol, stock_field::ASK_SIZE, askSize);
            break;
        case 'o':
            open = set_price(pField->field_value);
            observers(packetTime, symbol, stock_field::OPEN, open);
            break;
        case 't':
            last = set_price(pField->field_value);
            observers(packetTime, symbol, stock_field::LAST, last);
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
