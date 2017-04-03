//
// Created by b.karjoo on 3/30/2017.
//

#include "launch_rules.h"
#include <iostream>

void launch_rules::add_date(int year, int month, int day) {
    std::shared_ptr<tm> d1 = std::make_shared<tm>();
    d1->tm_year = year;
    d1->tm_mon = month - 1;
    d1->tm_mday = day;
    dates.push_back(d1);
}

std::string launch_rules::to_string() const {
    std::string s = "";

    for (auto& a : dates) {
        if (s != "") s += '\n';
        s += std::to_string(a->tm_year); s += '-';
        s += std::to_string(a->tm_mon + 1); s += '-';
        s += std::to_string(a->tm_mday);
    }
    return s;
}

const std::vector<std::shared_ptr<tm>> &launch_rules::getDates() const {
    return dates;
}
