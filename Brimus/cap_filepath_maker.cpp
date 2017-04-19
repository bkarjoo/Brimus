//
// Created by Behrooz Karjoo on 4/15/17.
//

#include "cap_filepath_maker.h"

void cap_filepath_maker::add_launch_rules(const strategy_launch_rules & lr) {
    auto d = lr.getDates();
    for (auto& a : d)
        dates.insert(a);
}

void cap_filepath_maker::construct_paths() {
    for (auto a : dates) {
        std::stringstream ss;
        ss << "E:\\" << a.year() << "\\";
        ss << a.year() << '-';
        if (a.month().as_number() < 10) ss << '0';
        ss << a.month().as_number() << '-';
        if (a.day() < 10) ss << '0';
        ss << a.day();
        ss << ".CAP";
        paths.push_back(ss.str());
    }
}

const std::vector<std::string> &cap_filepath_maker::get_paths() {
    return paths;
}


