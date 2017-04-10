//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_LAUNCH_RULES_H
#define BRIMUS_LAUNCH_RULES_H

#include "stdafx.h"
#include "holidays.h"
#include "Date_Compare.h"

class launch_rules {
    typedef boost::gregorian::date bdate;
    typedef std::shared_ptr<bdate> date_ptr;
    typedef std::set<date_ptr, Date_Compare> date_set;
    date_set dates;
    date_ptr startDate;
    date_ptr endDate;
public:
    const date_set &getDates() const;
    launch_rules() {}
    ~launch_rules() {}
    void add_date(int year, int month, int day);
    std::string to_string() const;
    void set_date_range();
    const date_ptr &getStartDate() const;
    void setStartDate(int year, int month, int day);
    const date_ptr &getEndDate() const;
    void setEndDate(int year, int month, int day);
    bool is_holiday(date_ptr date);
    bool is_holiday(bdate date);
};




#endif //BRIMUS_LAUNCH_RULES_H
