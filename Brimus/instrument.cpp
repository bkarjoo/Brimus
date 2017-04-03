//
// Created by b.karjoo on 3/21/2017.
//

#include "instrument.h"
#include <cmath>
#include <iostream>

/*
 * pcap_file class has a vector of instruments to which it sends messages
 */
void instrument::on_message(std::shared_ptr<st_message> msg) {
//    std::cout << msg->to_string() << std::endl;
//    std::cout << msg->get_fields().size() << std::endl;
    for (auto a : msg->get_fields()) {
        register_field(a);
    }
    for (auto a : update_observer) a(symbol);
    PropertyChanged(*this, symbol);
}

const std::string &instrument::getSymbol() const {
    return symbol;
}

void instrument::setSymbol(const std::string &symbol) {
    instrument::symbol = symbol;
}

//void instrument::set_strategy(instrument_observer *s) {
//    my_strategy = s;
//}

void instrument::register_field(st_field *pField) {
    switch (pField->field_code) {
        case 'a':
            ask_price = set_price(pField->field_value);
            break;
        case 'b':
            bid_price = set_price(pField->field_value);
            break;
        case 'f':
            if (pField->field_code_value == "") {
                set_precision(pField);
                break;
            }
        case 'g':
            if (pField->field_code_value == "77") {
                last_time_stamp = pField->field_value;
            }
            break;
        case 'j':
            bid_size = set_volume(pField->field_value);
            break;
        case 'k':
            ask_size = set_volume(pField->field_value);
            break;
        case 'o':
            open_price = set_price(pField->field_value);
            break;
        case 't':
            last_price = set_price(pField->field_value);
            for (auto a : last_observers) if (a) a(last_time_stamp, last_price);
            break;
        case 'y':
            close_price = set_price(pField->field_value);
            break;
    }
}

double instrument::set_price(const std::string & price) {
    try {

        double d = stod(price);
        return d / pow(10,precision);
    } catch (...) {
        return 0;
    }
}

unsigned int instrument::set_volume(const std::string & vol) {
    try {
        int i = stoi(vol);
        if (vol[0] == '-')
            return i * -1;
        else
            return i * 100;
    } catch (...) {
        return 0;
    }
}

void instrument::set_precision(st_field *f) {
    try {
        precision = stoi(f->field_value);
    } catch (...) {

    }
}


const std::string &instrument::getLast_time_stamp() const {
    return last_time_stamp;
}

void instrument::setLast_observer(const std::function<void(std::string, double)> &last_observer) {
    last_observers.push_back(last_observer);
}

void instrument::setUpdate_observer(const std::vector<std::function<void(std::string)>> &update_observer)
{
    this->update_observer = update_observer;

}

instrument::instrument(std::string symb, std::function<void(std::string)> callback)  :
        symbol(symb)
{
    update_observer.push_back(callback);
    std::cout << "New Instrument 2 param." << std::endl;
    instance_count++;
}

int instrument::instance_count = 0;