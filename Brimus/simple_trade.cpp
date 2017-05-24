//
// Created by b.karjoo on 5/3/2017.
//

#include "simple_trade.h"

using namespace std;

simple_trade::simple_trade(std::shared_ptr<simple_order> o) {
    entryOrders.add_order(o);
}

// TODO : throw an exception if symbol doesn't match
void simple_trade::add_order(std::shared_ptr<simple_order> o) {
    bool isEntry = (getSide() == "Long" && o->getOriginalQuantity() > 0)
        || (getSide() == "Short" && o->getOriginalQuantity() < 0);
    if (isEntry) entryOrders.add_order(o); else exitOrders.add_order(o);
}

double simple_trade::average_entry_price() {
    return entryOrders.average_price();
}

double simple_trade::average_exit_price() {
    return exitOrders.average_price();
}


boost::optional<boost::posix_time::ptime> simple_trade::first_entry_time() {
    return entryOrders.first_execution_time();

}

boost::optional<boost::posix_time::ptime> simple_trade::first_exit_time() {
    return exitOrders.first_execution_time();
}

boost::optional<boost::posix_time::ptime> simple_trade::last_entry_time() {
    return entryOrders.last_execution_time();
}

boost::optional<boost::posix_time::ptime> simple_trade::last_exit_time() {
    return exitOrders.last_execution_time();
}

int simple_trade::entry_execution_quantity() {
    return entryOrders.execution_quantity();
}

int simple_trade::exit_execution_quantity() {
    return exitOrders.execution_quantity();
}

bool simple_trade::is_closed() {
    return entry_execution_quantity() == exit_execution_quantity();
}

bool simple_trade::is_open() {
    return entry_execution_quantity() != exit_execution_quantity();
}

int simple_trade::closed_quantity() {
    return exit_execution_quantity();
}

int simple_trade::open_quantity() {
    return entry_execution_quantity() - exit_execution_quantity();
}

std::string simple_trade::getSymbol() {
    return *entryOrders.get_symbol();
}

std::string simple_trade::getSide() {
    return *entryOrders.get_side();
}

double simple_trade::entry_dollar_value() {
    return entryOrders.dollar_value();
}

double simple_trade::exit_dollar_value() {
    return exitOrders.dollar_value();
}

double simple_trade::dollar_difference() {
    return exit_dollar_value() - entry_dollar_value();
}

// TODO : this calculation seems off to me, check
double simple_trade::cents_per_share() {
    return dollar_difference() / (entry_execution_quantity() / 2) / 100;
}

double simple_trade::exposure() {
    return entry_dollar_value()>exit_dollar_value()
           ?entry_dollar_value()
           :exit_dollar_value();
}


double simple_trade::open_profit_or_loss(double currentPrice) {
    return (currentPrice - average_entry_price()) * open_quantity();
}

// TODO : doesn't seem right, this will only work for closed trades, partials?
double simple_trade::closed_profit_or_loss() {
    return dollar_difference();
}

std::string simple_trade::csv_stats() {
    using namespace boost::gregorian; 
    boost::posix_time::ptime t1;
    boost::posix_time::ptime t2;
    if (first_entry_time()) t1 = *first_entry_time();
    if (last_exit_time()) t2 = *last_exit_time();
    int year1 = t1.date().year();
    int month1 = t1.date().month().as_number();
    int day1 = t1.date().day();
    int hour1 = t1.time_of_day().hours();
    int minute1 = t1.time_of_day().minutes();
    int seconds1 = t1.time_of_day().seconds();
    int year2 = t2.date().year();
    int month2 = t2.date().month().as_number();
    int day2 = t2.date().day();
    int hour2 = t2.time_of_day().hours();
    int minute2 = t2.time_of_day().minutes();
    int seconds2 = t2.time_of_day().seconds();
    string t1str = to_string(year1) + '-' + to_string(month1) + '-' + to_string(day1) + ' ' 
        + to_string(hour1) + ':' + to_string(minute1) + ':' + to_string(seconds1);
    string t2str = to_string(year2) + '-' + to_string(month2) + '-' + to_string(day2) + ' '
                   + to_string(hour2) + ':' + to_string(minute2) + ':' + to_string(seconds2);

    return getSymbol() + ',' +
    t1str + ',' +
    t2str + ',' +
    getSide() + ',' +
    to_string(cents_per_share()) + ',' +
    to_string(dollar_difference()) + ',' +
    to_string(total_executed_quantity()) + ',' +
    to_string(exposure());
}

int simple_trade::total_executed_quantity() {
    return entry_execution_quantity() + exit_execution_quantity();
}












