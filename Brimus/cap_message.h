//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_ST_MESSAGE_H
#define BRIMUS_ST_MESSAGE_H
#include "stdafx.h"
#include "cap_msg_field.h"

class cap_message {
public:
    cap_message() {}
    cap_message(char prefix, std::string &symbol);
    cap_message(char prefix);
    ~cap_message() {
        for (auto a: fields) { delete a; a = nullptr; }
    }
    void add_field(const char& fCode, std::string& fCodeVal, std::string& fVal, const char& fExch);
    std::string  to_string() const;

    char getPrefix() const;

    void set_prefix(const char&);
    void set_symbol(std::string& symb);
    // make these unique pointers to keep them
    const std::vector<cap_msg_field*>& get_fields() const;
    const std::string &getSymbol() const;
    char getDelim() const;
    void setDelim(char delim);
private:
    std::vector<cap_msg_field*> fields;
    std::string symbol = "";
    char prefix = 0;
    char delim = 0;


};


#endif //BRIMUS_ST_MESSAGE_H
