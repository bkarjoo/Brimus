//
// Created by b.karjoo on 4/4/2017.
//

#include "tick_file_maker.h"






const std::string &tick_file_maker::getOutput_path() const {
    return output_path;
}

void tick_file_maker::setOutput_path(const std::string &output_path) {
    tick_file_maker::output_path = output_path;
}

void tick_file_maker::on_message(const cap_message &message) {
    *os << message.to_string();
}

bool tick_file_maker::has_instrument(const std::string & symbol) {
    return symbol_list.find(symbol) != symbol_list.end();
}
