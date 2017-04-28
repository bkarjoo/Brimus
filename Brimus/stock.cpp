//
// Created by Behrooz Karjoo on 4/16/17.
//

#include "stock.h"

using namespace boost;
using namespace boost::signals2;
using namespace std;

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
    if (capType == cap_file_type::FULL) {
        return to_boost_ptime(last_timestamp);
    } else {
        return packetTime;
    }
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
        case 'f':
            if (pField->field_code_value == "") {
                // TODO : precision has a default value of 4

                // TODO : how do I tell if I should use precision or not?
                // TODO : instead of being compatible with both, have a mode.
                    // TODO : create the mode
                // compact files will not have precision
                // the tell is that they have a . in the value
                set_precision(pField->field_value);
                break;
            }
        case 'g':
            if (pField->field_code_value == "77") {
                last_timestamp = pField->field_value;
            }
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
    time_set = true;
}

cap_file_type stock::getCapType() const {
    return capType;
}

void stock::setCapType(cap_file_type capType) {
    stock::capType = capType;
}

const stock::ptime &stock::to_boost_ptime(const string& t) const {
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0, hours, minutes, seconds;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        seconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; seconds = std::stoi(ss);

    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; seconds = std::stoi(ss);

    }

    // TODO : construct time duration
    boost::posix_time::time_duration td(hours,minutes,seconds,0);


    return boost::posix_time::ptime(dt,td);
}

void stock::set_precision(const std::string &field_value) {
        try {
            precision = stoi(field_value);
        } catch (...) {

        }
    }

const gregorian::date &stock::getDt() const {
    return dt;
}

void stock::setDt(const gregorian::date &dt) {
    stock::dt = dt;
}

bool stock::isTime_set() const {
    return time_set;
}

void stock::setTime_set(bool time_set) {
    stock::time_set = time_set;
}




