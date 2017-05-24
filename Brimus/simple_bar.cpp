//
// Created by b.karjoo on 5/1/2017.
//

#include "simple_bar.h"

simple_bar::simple_bar(const boost::posix_time::ptime &startTime, double open) : startTime(startTime), open(open) {
    high = open;
    low = open;
    close = open;
}

void simple_bar::add_price(double price) {
    close = price;
    if (price > high) high = price;
    if (price < low) {
        low = price;
    }
}

double simple_bar::getOpen() const {
    return open;
}

const boost::posix_time::ptime &simple_bar::getStartTime() const {
    return startTime;
}

double simple_bar::getHigh() const {
    return high;
}

double simple_bar::getLow() const {
    return low;
}

double simple_bar::getClose() const {
    return close;
}
