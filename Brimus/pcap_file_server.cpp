//
// Created by b.karjoo on 3/30/2017.
//

#include <boost/shared_ptr.hpp>
#include "pcap_file_server.h"


void pcap_file_server::request_data(std::shared_ptr<launch_rules> launchRules) {
    auto d = launchRules->getDates();
    for (auto& a : d)
        dates.insert(a);
}

const pcap_file_server::date_set &pcap_file_server::getDates() const {
    return dates;
}

const std::vector<std::string> &pcap_file_server::get_paths() {
    if (paths.size() == 0) construct_paths();
    return paths;
}

// after dates are set, the paths are constructed from them
void pcap_file_server::construct_paths() {
    for (auto a : dates) {
        std::stringstream ss;
        ss << "E:\\" << a->year() << "\\";
        ss << a->year() << '-';
        if (a->month().as_number() < 10) ss << '0';
        ss << a->month().as_number() << '-';
        if (a->day() < 10) ss << '0';
        ss << a->day();
        ss << ".CAP";
        paths.push_back(ss.str());
    }
}




