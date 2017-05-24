//
// Created by b.karjoo on 5/1/2017.
//

#include "simple_bar_series_check.h"

simple_bar_series::simple_bar_series(
        const boost::posix_time::time_duration &interval)
        : interval(interval) {

}

void simple_bar_series::add_price(boost::posix_time::ptime tickTime, double last) {
    if (new_bar_needed(tickTime))
        addBar(tickTime, last);
    else
        currentBar->add_price(last);
}

void simple_bar_series::addBar(boost::posix_time::ptime time, double price) {
    simple_bar* b = new simple_bar(time, price);
    currentBar = b;
    bars.push_back(b);
}

simple_bar_series::~simple_bar_series() {
    for (auto b : bars) {
        delete b; b = nullptr;
    }
}

bool simple_bar_series::new_bar_needed(boost::posix_time::ptime time) {
    if (currentBar == nullptr) return true;
    if (currentBar->getStartTime().time_of_day().minutes()
            == time.time_of_day().minutes()) return false;
    auto nextBarStartMinute = currentBar->getStartTime() + interval;
    return (nextBarStartMinute.time_of_day().minutes()
        == time.time_of_day().minutes());
}
