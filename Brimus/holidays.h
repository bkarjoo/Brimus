//
// Created by b.karjoo on 4/3/2017.
//

#ifndef BRIMUS_HOLIDAYS_H
#define BRIMUS_HOLIDAYS_H


#include "stdafx.h"

class holidays {
    typedef boost::gregorian::date bdate;
    std::set<bdate> dates;
    holidays() {}
    ~holidays() {}
    const std::string holiday_file = "holidays.txt";
    void load_holidays();
public:
    holidays(holidays const&) = delete;
    void operator=(holidays const&) = delete;
    static holidays& get_instance() {
        static holidays h;
        if (h.dates.size() == 0) h.load_holidays();
        return h;
    }
    const std::set<bdate>& getHolidays() { return dates; }
};


#endif //BRIMUS_HOLIDAYS_H
