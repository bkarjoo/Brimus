//
// Created by b.karjoo on 3/30/2017.
//

#include "date.h"

date::date(int month, int day, int year) : month(month), day(day), year(year) {}

int date::getMonth() const {
    return month;
}

void date::setMonth(int month) {
    date::month = month;
}

int date::getDay() const {
    return day;
}

void date::setDay(int day) {
    date::day = day;
}

int date::getYear() const {
    return year;
}

void date::setYear(int year) {
    date::year = year;
}
