//
// Created by b.karjoo on 3/23/2017.
//

#ifndef BRIMUS_TIME_H
#define BRIMUS_TIME_H

#include <string>

class invalid_time_format: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Expected 6 character: hhmmss or 8-9 character: (h)hmmsslll : hours,minutes,seconds,milliseconds.";
    }
};


class btime {
    unsigned short int hours = 0; // 0 to 23
    unsigned short int minutes = 0; // 0 to 59
    unsigned short int seconds = 0; // 0 to 59
    unsigned short int milliseconds = 0; // 0 to 999
public:
    btime() {}
    btime(std::string time_str); // format hhmmss (6 digit), or (h)hmmssmmm (8 or 9 digit)
    btime(unsigned short int hours, unsigned short int minutes);
    unsigned short getHours() const { return hours; }
    unsigned short getMinutes() const { return minutes; }
    unsigned short getSeconds() const { return seconds; }
    unsigned short getMilliseconds() const { return milliseconds; }
    int seconds_from_midnight() const; // ignores milliseconds
    int milliseconds_from_midnight() const;
    bool operator<(const btime& other) const;
    bool operator>(const btime& other) const;
    bool operator==(const btime& other) const;
    std::string to_string() const;
    void update(const std::string& timestamp);
    bool isGreaterThan(std::string);
    bool isLessThan(std::string);
    bool isEqualTo(std::string);
    void setHours(unsigned short hours);
    void setMinutes(unsigned short minutes);
    void setSeconds(unsigned short seconds);
    void setMilliseconds(unsigned short milliseconds);
};


#endif //BRIMUS_TIME_H
