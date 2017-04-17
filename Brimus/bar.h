//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_BAR_H
#define BRIMUS_BAR_H


#include "btime.h"

class bar {
    btime startTime;
    double _open = 0.0;
    double _high = 0.0;
    double _low = 100000.0;
    double _close = 0.0;
public:
    bar() {}
    bar(btime b) { startTime.setHours(b.getHours()); startTime.setMinutes(b.getMinutes()); }
    bar(unsigned short int hour, unsigned short int minute);

    void setStartTime(const btime &startTime);

    const btime &getStartTime() const;

    double range() { return _high - _low; }

    void add_tick(std::string timestamp, double price);

    double get_open() const;

    double get_high() const;

    double get_low() const;

    double get_close() const;

    bool operator<(bar& other) {
        return startTime < other.startTime;
    }

    bool operator>(bar& other) {
        return startTime > other.startTime;
    }
};

#endif //BRIMUS_BAR_H
