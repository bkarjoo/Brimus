//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_ST_MESSAGE_PRINTER_H
#define BRIMUS_ST_MESSAGE_PRINTER_H


#include "instrument.h"

class st_message_printer : public instrument {
    std::shared_ptr<std::ofstream> of;
    std::string output_path = "";
public:
    st_message_printer(std::string symbol) : instrument(symbol) {}
    void create_ofstream();

    void setOutput_path(const std::string &output_path);
};


#endif //BRIMUS_ST_MESSAGE_PRINTER_H
