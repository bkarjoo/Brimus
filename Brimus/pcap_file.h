//
// Created by b.karjoo on 3/20/2017.
//

#ifndef BRIMUS_PCAP_FILE_H
#define BRIMUS_PCAP_FILE_H

#include "stdafx.h"
#include "read_mode.h"
#include "ISTNotifier.h"
#include "st_message.h"
#include "instrument.h"

class pcap_file {
    pcap_file() {}
    std::set<std::string> symbols;
    int start_time_seconds = 0, end_time_seconds = 86399;

    read_mode mode = read_mode::PACKET_HEADER;
    bool is_packet_delimiter(const char &c);
    bool is_msg_delimiter(const char &c, const char &prev);
    bool is_upper_case(const char &c);
    bool is_field_delimiter(const char &c, const char &prev);
    bool is_lower_case(const char &c);
    std::string get_full_path(std::string date, std::string symbol);
    // TODO: deletion candidates, notifier class to be replaced by global_basket
    std::shared_ptr<ISTNotifier> notifier;
public:
    // static construction
    void operator=(pcap_file const&) = delete;
    pcap_file(pcap_file const&) = delete;
    static pcap_file& get_instance();
    // getters and setters
    int getStart_time_seconds() const;
    void setStart_time_seconds(int start_time_seconds);
    int getEnd_time_seconds() const;
    void setEnd_time_seconds(int end_time_seconds);
    void run(const std::vector<std::string> &file_paths);
    void add_instrument(std::string);
    void add_instrument(std::shared_ptr<instrument>);
    void set_notifier(std::shared_ptr<ISTNotifier> istn) { notifier = istn; }
};


#endif //BRIMUS_PCAP_FILE_H
