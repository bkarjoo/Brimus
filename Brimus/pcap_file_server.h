//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_PCAP_FILE_SERVER_H
#define BRIMUS_PCAP_FILE_SERVER_H

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
    std::set<std::shared_ptr<tm>> dates;
public:
    const std::set<std::shared_ptr<tm>> &getDates() const;

private:
    std::vector<std::string> paths;
    pcap_file_server() {}
    ~pcap_file_server() {}
public:
    pcap_file_server(pcap_file_server const&) = delete;
    void operator=(pcap_file_server const&) = delete;
    static pcap_file_server& get_instance() {
        static pcap_file_server pfs;
        return pfs;
    }
    std::vector<std::string>& get_paths() {
        paths.push_back("C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40000.CAP");
        paths.push_back("C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40001.CAP");
        paths.push_back("C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40002.CAP");
        paths.push_back("C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40003.CAP");
        return paths;
    };

    void request_data(std::shared_ptr<launch_rules> ptr) override;
};


#endif //BRIMUS_PCAP_FILE_SERVER_H
