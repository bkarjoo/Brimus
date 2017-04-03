//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_PCAP_FILE_SERVER_H
#define BRIMUS_PCAP_FILE_SERVER_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "launch_rules.h"
#include "IDataServer.h"

/*
 * responsible for producing the file paths and file management on discs
 */
class pcap_file_server : public IDataServer {
    typedef boost::gregorian::date bdate;
    typedef std::shared_ptr<bdate> date_ptr;
    typedef std::set<date_ptr, Date_Compare> date_set;
    date_set dates;
    std::vector<std::string> paths;
    pcap_file_server() {}
    ~pcap_file_server() {}
public:
    const date_set &getDates() const;
    pcap_file_server(pcap_file_server const&) = delete;
    void operator=(pcap_file_server const&) = delete;
    static pcap_file_server& get_instance() {
        static pcap_file_server pfs;
        return pfs;
    }
    void construct_paths();
    const std::vector<std::string>& get_paths();
    void clear_date_set() { dates.clear(); }
    void request_data(std::shared_ptr<launch_rules> ptr) override;


};


#endif //BRIMUS_PCAP_FILE_SERVER_H
