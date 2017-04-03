//
// Created by b.karjoo on 3/21/2017.
//

#include "st_message_printer.h"
void st_message_printer::create_ofstream() {
    std::string name = output_path + symbol + ".CAP";
    of = std::make_shared<std::ofstream>(name);
}

void st_message_printer::setOutput_path(const std::string &output_path) {
    st_message_printer::output_path = output_path;
}