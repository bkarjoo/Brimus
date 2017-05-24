//
// Created by b.karjoo on 5/1/2017.
//

#ifndef BRIMUS_SIMPLE_BAR_H
#define BRIMUS_SIMPLE_BAR_H

#include <ostream>
#include "stdafx.h"

class simple_bar {
    boost::posix_time::ptime startTime;
    double open = 0.0;
    double high = 0.0;
    double low = 0.0;
    double close = 0.0;
public:
    simple_bar(const boost::posix_time::ptime &startTime, double open);

    void add_price(double price);

    double getOpen() const;

    double getHigh() const;

    double getLow() const;

    double getClose() const;

    const boost::posix_time::ptime &getStartTime() const;

    friend std::ostream &operator<<(std::ostream &os, const simple_bar &simpleBar){
        os << "startTime: " << simpleBar.startTime << " open: " << simpleBar.open << " high: " << simpleBar.high << " low: "
           << simpleBar.low << " close: " << simpleBar.close;
        return os;
    }

};


#endif //BRIMUS_SIMPLE_BAR_H
