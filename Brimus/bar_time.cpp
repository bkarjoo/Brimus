//
// Created by b.karjoo on 3/23/2017.
//

#include "bar_time.h"

bar_time::bar_time(const boost::posix_time::ptime & bt) {
    hours = bt.time_of_day().hours();
    minutes = bt.time_of_day().minutes();
    seconds = bt.time_of_day().seconds();
}


bar_time::bar_time(std::string t)
{
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        seconds = 0; milliseconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; seconds = std::stoi(ss);
        milliseconds = 0;
    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; seconds = std::stoi(ss);
        for ( ; i < j+7 ; ++ i) ms += t[i]; milliseconds = std::stoi(ms);
    } else {
        throw invalid_time_format();
    }
}

int bar_time::seconds_from_midnight() const
{
    return ((hours * 60) + minutes) * 60 + seconds;
}

int bar_time::milliseconds_from_midnight() const
{
    return (seconds_from_midnight() * 1000) + milliseconds;
}

std::string bar_time::to_string() const
{
    std::string hour_str = "", minute_str = "", second_str = "", ms_str = "";
    if (hours < 10) hour_str += '0'; hour_str += std::to_string(hours);
    if (minutes < 10) minute_str += '0'; minute_str += std::to_string(minutes);
    if (seconds < 10) second_str += '0'; second_str += std::to_string(seconds);
    if (milliseconds < 100) ms_str += '0'; if (milliseconds < 10) ms_str += "0";
    ms_str += std::to_string(milliseconds);
    return hour_str + minute_str + second_str + ms_str;
}

bool bar_time::operator<(const bar_time& other) const
{
    return milliseconds_from_midnight() < other.milliseconds_from_midnight();
}

bool bar_time::operator>(const bar_time& other) const
{
    return milliseconds_from_midnight() > other.milliseconds_from_midnight();
}

bool bar_time::operator==(const bar_time& other) const
{
    return milliseconds_from_midnight() == other.milliseconds_from_midnight();
}

void bar_time::update(const std::string &t) {
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        seconds = 0; milliseconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; seconds = std::stoi(ss);
        milliseconds = 0;
    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; seconds = std::stoi(ss);
        for ( ; i < j+7 ; ++ i) ms += t[i]; milliseconds = std::stoi(ms);
    } else {
        throw invalid_time_format();
    }
}

bool bar_time::isGreaterThan(std::string t) {
    bar_time x = bar_time("00000000");
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        x.seconds = 0; x.milliseconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        x.milliseconds = 0;
    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; x.hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        for ( ; i < j+7 ; ++ i) ms += t[i]; x.milliseconds = std::stoi(ms);
    } else {
        throw invalid_time_format();
    }
    return *this > x;
}

bool bar_time::isLessThan(std::string t) {
    bar_time x = bar_time("00000000");
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        x.seconds = 0; x.milliseconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        x.milliseconds = 0;
    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; x.hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        for ( ; i < j+7 ; ++ i) ms += t[i]; x.milliseconds = std::stoi(ms);
    } else {
        throw invalid_time_format();
    }
    return *this < x;
}

bool bar_time::isEqualTo(std::string t) {
    bar_time x = bar_time("00000000");
    std::string hh = "", mm = "", ss = "", ms = "";
    int i = 0;
    if (t.length() == 4) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        x.seconds = 0; x.milliseconds = 0;
    } else if (t.length() == 6) {
        for ( ; i < 2 ; ++i ) hh += t[i];  x.hours = std::stoi(hh);
        for ( ; i < 4 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < 6 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        x.milliseconds = 0;
    } else if(t.length() >= 8 && t.length() <= 9) {
        int j; t.length() == 8 ? j = 1 : j = 2;
        for ( ; i < j ; ++i ) hh += t[i]; x.hours = std::stoi(hh);
        for ( ; i < j+2 ; ++i ) mm += t[i]; x.minutes = std::stoi(mm);
        for ( ; i < j+4 ; ++ i) ss += t[i]; x.seconds = std::stoi(ss);
        for ( ; i < j+7 ; ++ i) ms += t[i]; x.milliseconds = std::stoi(ms);
    } else {
        throw invalid_time_format();
    }
    return *this == x;
}

bar_time::bar_time(int h, int m) {
    hours = h;
    minutes = m;
}

void bar_time::setHours(int hours) {
    bar_time::hours = hours;
}

void bar_time::setMinutes(int minutes) {
    bar_time::minutes = minutes;
}

void bar_time::setSeconds(int seconds) {
    bar_time::seconds = seconds;
}

void bar_time::setMilliseconds(int milliseconds) {
    bar_time::milliseconds = milliseconds;
}




