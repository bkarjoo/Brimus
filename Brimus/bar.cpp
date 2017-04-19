//
// Created by b.karjoo on 3/24/2017.
//
#include "bar.h"

void bar::add_tick(std::string timestamp, double price) {
    if (_open == 0) _open = price;
    if (price > _high) _high = price;
    if (price < _low) _low = price;
    _close = price;
}

double bar::get_open() const {
    return _open;
}

double bar::get_high() const {
    return _high;
}

double bar::get_low() const {
    return _low;
}

double bar::get_close() const {
    return _close;
}

bar::bar(unsigned short int hour, unsigned short int minute) {
    startTime.setHours(hour);
    startTime.setMinutes(minute);
}

const bar_time &bar::getStartTime() const {
    return startTime;
}


void bar::setStartTime(const bar_time &startTime) {
    bar::startTime = startTime;
}

void bar::add_tick(double price) {
    if (_open == 0) _open = price;
    if (price > _high) _high = price;
    if (price < _low) _low = price;
    _close = price;
}

