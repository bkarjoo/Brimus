//
// Created by b.karjoo on 4/4/2017.
//

#include "tick_file_maker.h"



void tick_file_maker::notify(std::shared_ptr<st_message> ptr) {
    *os << ptr->to_string();
}

void tick_file_maker::add_instrument(std::shared_ptr<instrument> ptr) {

}

void tick_file_maker::add_instrument(std::string string) {

}

const std::string &tick_file_maker::getOutput_path() const {
    return output_path;
}

void tick_file_maker::setOutput_path(const std::string &output_path) {
    tick_file_maker::output_path = output_path;
}
