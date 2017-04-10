//
// Created by b.karjoo on 4/3/2017.
//

#ifndef BRIMUS_HOLIDAYS_H
#define BRIMUS_HOLIDAYS_H


#include "stdafx.h"
#include "Date_Compare.h"

class holidays {
    typedef boost::gregorian::date bdate;
    typedef std::shared_ptr<bdate> date_ptr;
    typedef std::set<date_ptr, Date_Compare> date_set;
    date_set dates;
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
    const date_set& getHolidays() { return dates; }
};


#endif //BRIMUS_HOLIDAYS_H
