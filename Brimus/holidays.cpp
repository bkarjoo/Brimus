//
// Created by b.karjoo on 4/3/2017.
//

#include "holidays.h"


void holidays::load_holidays() {
    std::ifstream fs(holiday_file);
    std::string line;
    while (std::getline(fs, line)) {
        std::string year_str = line.substr(0,4);
        std::string month_str = line.substr(4,2);
        std::string day_str = line.substr(6,2);
        int year = std::stoi(year_str);
        int month = std::stoi(month_str);
        int day = std::stoi(day_str);
        dates.insert(bdate(year,month,day));
    }
}
