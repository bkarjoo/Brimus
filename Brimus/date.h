//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_DATE_H
#define BRIMUS_DATE_H


class date {
private:
    int month;
    int day;
    int year;
public:
    date(int month, int day, int year);

    int getMonth() const;

    void setMonth(int month);

    int getDay() const;

    void setDay(int day);

    int getYear() const;

    void setYear(int year);

    // TODO : make this a wrapper of the boost date class

//    inline bool operator<(const date& other) { return this->daysFromDay1() < other.daysFromDay1(); }
//    inline bool operator>(const date& other) { return this->daysFromDay1() > other.daysFromDay1(); }
//    inline bool operator==(const date& other) { return this->daysFromDay1() == other.daysFromDay1(); }
//    int daysFromDay1() const { return year * 365 + month * 30 + day; }


};


#endif //BRIMUS_DATE_H
