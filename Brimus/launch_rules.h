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
    typedef std::set<bdate> date_set;
    date_set dates;
    boost::optional<bdate> startDate;
    boost::optional<bdate> endDate;
public:
    const date_set &getDates() const;
    launch_rules() {}
    ~launch_rules() {}
    void add_date(int year, int month, int day);
    std::string to_string() const;
    void set_date_range();
    boost::optional<launch_rules::bdate> getStartDate() const;
    void setStartDate(int year, int month, int day);
    boost::optional<launch_rules::bdate> getEndDate() const;
    void setEndDate(int year, int month, int day);
    bool is_holiday(bdate date);
};




#endif //BRIMUS_LAUNCH_RULES_H
