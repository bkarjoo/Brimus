//
// Created by b.karjoo on 4/4/2017.
//

#ifndef BRIMUS_TICK_FILE_MAKER_H
#define BRIMUS_TICK_FILE_MAKER_H

#include <fstream>
#include <memory>
#include <string>
#include <functional>
#include "ISTNotifier.h"

class tick_file_maker : public ISTNotifier {
    typedef std::shared_ptr<std::ofstream> os_ptr;
    os_ptr os = nullptr;
    std::string output_path = "";

public:
    tick_file_maker(std::string out_path) : output_path(out_path) {
        os = std::make_shared<std::ofstream>(out_path);
    }
    const std::string &getOutput_path() const;

    void setOutput_path(const std::string &output_path);

public:
    void notify(std::shared_ptr<st_message> ptr) override;

    void add_instrument(std::shared_ptr<instrument> ptr) override;

    void add_instrument(std::string string) override;

    void close_os() { os->close(); }
};


#endif //BRIMUS_TICK_FILE_MAKER_H
