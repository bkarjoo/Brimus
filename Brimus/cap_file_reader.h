//
// Created by Behrooz Karjoo on 4/15/17.
//
#ifndef BRIMUS_CAP_FILE_READER_H
#define BRIMUS_CAP_FILE_READER_H

#include "stdafx.h"
#include "read_mode.h"
#include "st_field.h"
#include "st_message.h"
#include "IMessageReceiver.h"

/*
 * get singleton instance
 * call setImr with your implementation of IMessageReceiver
 * optionally set start and end time of day to read from packet files
 * call run with a vector of file_paths to process
 */
class cap_file_reader {
public:
    cap_file_reader(cap_file_reader&) = delete;
    void operator=(cap_file_reader const&) = delete;
    static cap_file_reader& get_instance() { static cap_file_reader cfr; return cfr; }
    void run(const std::vector<std::string> &file_paths);
    int getStart_time_seconds() const;
    void setStart_time_seconds(int start_time_seconds);
    int getEnd_time_seconds() const;
    void setEnd_time_seconds(int end_time_seconds);
    void setImr(std::unique_ptr<IMessageReceiver>);
private:
    cap_file_reader() {}
    ~cap_file_reader() {}
    int start_time_seconds = 0;
    int end_time_seconds = 86399;
    read_mode mode = read_mode::PACKET_HEADER;
    bool is_packet_delimiter(const char &c);
    bool is_msg_delimiter(const char &c, const char &prev);
    bool is_upper_case(const char &c);
    bool is_field_delimiter(const char &c, const char &prev);
    bool is_lower_case(const char &c);
    std::unique_ptr<IMessageReceiver> imr;
};

#endif //BRIMUS_CAP_FILE_READER_H
