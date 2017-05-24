//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_TIME_H
#define BRIMUS_TIME_H
#include "stdafx.h"


class invalid_time_format: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Expected 6 character: hhmmss or 8-9 character: (h)hmmsslll : hours,minutes,seconds,milliseconds.";
    }
};

/*
 * a time class which is totally date agnostic
 */
class bar_time {
    int hours = 0; // 0 to 23
    int minutes = 0; // 0 to 59
    int seconds = 0; // 0 to 59
    int milliseconds = 0; // 0 to 999
public:
    //bar_time() {}
    bar_time(std::string time_str); // format hhmmss (6 digit), or (h)hmmssmmm (8 or 9 digit)
    bar_time(int hours, int minutes);
    bar_time(const boost::posix_time::ptime&);

    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }
    int getMilliseconds() const { return milliseconds; }
    int seconds_from_midnight() const; // ignores milliseconds
    int milliseconds_from_midnight() const;
    bool operator<(const bar_time& other) const;
    bool operator>(const bar_time& other) const;
    bool operator==(const bar_time& other) const;
    std::string to_string() const;
    void update(const std::string& timestamp);
    bool isGreaterThan(std::string);
    bool isLessThan(std::string);
    bool isEqualTo(std::string);
    void setHours(int hours);
    void setMinutes(int minutes);
    void setSeconds(int seconds);
    void setMilliseconds(int milliseconds);
};


#endif //BRIMUS_TIME_H
