//
// Created by b.karjoo on 3/30/2017.
//

#include "launch_rules.h"
#include <iostream>

void launch_rules::add_date(int year, int month, int day) {
    std::shared_ptr<boost::gregorian::date> d1 =
            std::make_shared<boost::gregorian::date>(year,month,day);
    dates.insert(d1);
}

std::string launch_rules::to_string() const {
    std::stringstream ss;
    for (auto& a : dates) {
        if (ss.str() != "") ss << '\n';
        ss << a->year() << '-';
        ss << a->month().as_number() << '-';
        ss << a->day();
    }
    return ss.str();
}

const launch_rules::date_set &launch_rules::getDates() const {
    return dates;
}

const launch_rules::date_ptr &launch_rules::getStartDate() const {
    return startDate;
}

void launch_rules::setStartDate(int year, int month, int day) {
    date_ptr startDate = std::make_shared<boost::gregorian::date>(year,month,day);
    launch_rules::startDate = startDate;
}

const launch_rules::date_ptr &launch_rules::getEndDate() const {
    return endDate;
}

void launch_rules::setEndDate(int year, int month, int day) {
    date_ptr endDate = std::make_shared<boost::gregorian::date>(year,month,day);
    launch_rules::endDate = endDate;
}

void launch_rules::set_date_range() {
    typedef boost::gregorian::date bdate;
    bdate start, end, dcounter;
    if (startDate)
        start = *startDate;
    else
        return; // TODO throw exception

    if (endDate)
        end = *endDate;
    else
        return; // TODO throw exception

    dcounter = start;

    boost::gregorian::date_duration dd(1);

    while (dcounter <= end) {

        if (dcounter.day_of_week() != boost::gregorian::Saturday
                && dcounter.day_of_week() != boost::gregorian::Sunday
                && !is_holiday(dcounter)) {
        add_date(dcounter.year(), dcounter.month().as_number(), dcounter.day());

      }
        dcounter += dd;
         
    }
}

bool launch_rules::is_holiday(date_ptr date) {
    holidays& h = holidays::get_instance();
    auto& hdays = h.getHolidays();
    return hdays.find(*date) != hdays.end();
}

bool launch_rules::is_holiday(bdate date) {
    holidays& h = holidays::get_instance();
    auto& hdays = h.getHolidays();
    return hdays.find(date) != hdays.end();
}
