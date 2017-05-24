//
// Created by b.karjoo on 5/1/2017.
//

#ifndef BRIMUS_SIMPLE_BAR_SERIES_H
#define BRIMUS_SIMPLE_BAR_SERIES_H
#include "stdafx.h"
#include "simple_bar.h"

class simple_bar_series {
    std::vector<simple_bar*> bars;
    boost::posix_time::time_duration interval;
    bool new_bar_needed(boost::posix_time::ptime time);
    simple_bar* currentBar = nullptr;
    void addBar(boost::posix_time::ptime time, double price);
public:
    simple_bar_series(const boost::posix_time::time_duration &interval);
    ~simple_bar_series();
    void add_price(boost::posix_time::ptime,double last);
    const simple_bar& CurrentBar() { return *currentBar; }

};


#endif //BRIMUS_SIMPLE_BAR_SERIES_H
