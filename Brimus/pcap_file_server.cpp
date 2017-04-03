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

const std::set<std::shared_ptr<tm>> &pcap_file_server::getDates() const {
    return dates;
}
