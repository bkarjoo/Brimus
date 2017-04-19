//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_BAR_H
#define BRIMUS_BAR_H


#include "bar_time.h"

class bar {
    bar_time startTime;
    double _open = 0.0;
    double _high = 0.0;
    double _low = 100000.0;
    double _close = 0.0;
public:
    bar() {}
    bar(bar_time b) { startTime.setHours(b.getHours()); startTime.setMinutes(b.getMinutes()); }
    bar(unsigned short int hour, unsigned short int minute);

    void setStartTime(const bar_time &startTime);

    const bar_time &getStartTime() const;

    double range() { return _high - _low; }

    void add_tick(std::string timestamp, double price);

    void add_tick(double price);

    double Open() const;

    double High() const;

    double Low() const;

    double Close() const;

    bool operator<(bar& other) {
        return startTime < other.startTime;
    }

    bool operator>(bar& other) {
        return startTime > other.startTime;
    }
};

#endif //BRIMUS_BAR_H
