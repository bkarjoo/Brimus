//
// Created by b.karjoo on 4/4/2017.
//

#ifndef BRIMUS_TICK_FILE_MAKER_H
#define BRIMUS_TICK_FILE_MAKER_H

#include "stdafx.h"
#include <functional>
#include "IMessageReceiver.h"

class tick_file_maker : public IMessageReceiver {
    // TODO : ofstreams can be made using unique ptr
    typedef std::shared_ptr<std::ofstream> os_ptr;
    os_ptr os = nullptr;
    std::string output_path = "";
    std::set<std::string> symbol_list;
public:
    tick_file_maker(std::string out_path) : output_path(out_path) {
        os = std::make_shared<std::ofstream>(out_path);
    }
    ~tick_file_maker() { os->close(); }

    const std::string &getOutput_path() const;

    void setOutput_path(const std::string &output_path);

public:

    void close_os() { os->close(); }

    void add_instrument(const std::string & symbol) { symbol_list.insert(symbol); }

    void on_message(const cap_message &message) override;

    bool has_instrument(const std::string &string) override;
};


#endif //BRIMUS_TICK_FILE_MAKER_H
