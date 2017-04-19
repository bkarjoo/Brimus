//
// Created by b.karjoo on 3/30/2017.
//

#include "strategy_launch_rules.h"

void strategy_launch_rules::add_date(int year, int month, int day) {
    dates.insert(bdate(year,month,day));
}

std::string strategy_launch_rules::to_string() const {
    std::stringstream ss;
    for (auto& a : dates) {
        if (ss.str() != "") ss << '\n';
        ss << a.year() << '-';
        ss << a.month().as_number() << '-';
        ss << a.day();
    }
    return ss.str();
}

const strategy_launch_rules::date_set &strategy_launch_rules::getDates() const {
    return dates;
}

boost::optional<strategy_launch_rules::bdate> strategy_launch_rules::getStartDate() const {
    if (startDate) return *startDate; else return {};
}

void strategy_launch_rules::setStartDate(int year, int month, int day) {
    strategy_launch_rules::startDate = bdate(year,month,day);
}

boost::optional<strategy_launch_rules::bdate> strategy_launch_rules::getEndDate() const {
    if (endDate) return *endDate; else return {};
}

void strategy_launch_rules::setEndDate(int year, int month, int day) {
    strategy_launch_rules::endDate = bdate(year,month,day);
}

void strategy_launch_rules::set_date_range() {
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

bool strategy_launch_rules::is_holiday(bdate date) {
    holidays& h = holidays::get_instance();
    auto& hdays = h.getHolidays();
    return hdays.find(date) != hdays.end();
}

