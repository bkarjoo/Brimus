//
// Created by b.karjoo on 4/4/2017.
//

#ifndef BRIMUS_TICK_FILE_MAKER_H
#define BRIMUS_TICK_FILE_MAKER_H

#include "stdafx.h"
#include <functional>
#include "IMessageReceiver.h"

struct dup_tracking {
    std::string symbol = "";
    //char f = 0;
    std::string v = "";
//    dup_tracking(std::string symb, char field, std::string value)
//        : symbol(symb), f(field), v(value) {}
    dup_tracking(std::string symb, std::string value) : symbol(symb), v(value){}
};

class tick_file_maker : public IMessageReceiver {
    // TODO : ofstreams can be made using unique ptr
    typedef std::shared_ptr<std::ofstream> os_ptr;
    os_ptr os = nullptr;
    std::string previous_symbol = "";
    std::string output_path = "";
    std::set<std::string> symbol_list;
    std::map<std::string, dup_tracking> dups;
    std::map<std::string, dup_tracking> lastBid;
    std::map<std::string, dup_tracking> lastAsk;
    std::map<std::string, dup_tracking> lastLast;
    std::map<std::string, dup_tracking> lastBidSize;
    std::map<std::string, dup_tracking> lastAskSize;
    std::map<std::string, dup_tracking> lastLastSize;
    bool is_dup(std::string symbol, char field, std::string value);
    void add_dup_tracker(std::string symbol, char field, std::string value);

public:
    tick_file_maker(std::string out_path) : output_path(out_path) {
        os = std::make_shared<std::ofstream>(out_path);
    }
    ~tick_file_maker() { os->close(); }

    const std::string &getOutput_path() const;

    void setOutput_path(const std::string &output_path);

    std::string format_price(int precision, const std::string &val);
    void flush_stream() { os->flush(); }

    void close_os() { os->close(); }

    void add_instrument(const std::string & symbol) { symbol_list.insert(symbol); }

    void on_message(const cap_message &message) override;

    bool has_instrument(const std::string &string) override;

    template<typename T>
    std::string to_str(const T &t) {
        std::string str{std::to_string(t)};
        int offset{1};
        if (str.find_last_not_of('0') == str.find('.')) { offset = 0; }
        str.erase(str.find_last_not_of('0') + offset, std::string::npos);
        return str;
    }

    void on_packet_header(const std::string &string) override;
};


#endif //BRIMUS_TICK_FILE_MAKER_H
