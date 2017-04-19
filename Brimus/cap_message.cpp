//
// Created by b.karjoo on 3/21/2017.
//


#include "cap_message.h"


void cap_message::add_field(const char &fCode, std::string &fCodeVal, std::string &fVal, const char &fExch) {
    cap_msg_field* f = new cap_msg_field();
    f->field_code = fCode;
    std::swap(f->field_code_value,fCodeVal);
    std::swap(f->field_value,fVal);
    if (fExch != 0) f->field_exchange = fExch;
    fields.push_back(f);
}

cap_message::cap_message(char pfix, std::string &symb) {
    prefix = pfix;
    std::swap(symb,symbol);
}

std::string & cap_message::to_string() const {
    std::string s;
    s += prefix;
    s += symbol;
    for (auto a : fields) {
        s += a->field_code;
        if (a->field_exchange != 0) s += a->field_exchange;
        if (a->field_code_value != "") {
            s += a->field_code_value;
            s += ',';
        }
        s += a->field_value;
    }
    return s;
}

cap_message::cap_message(char dlim) {
    delim = dlim;
}

void cap_message::set_prefix(const char &c) {
    prefix = c;
}

void cap_message::set_symbol(std::string &symb) {
    std::swap(symb,symbol);
}

const std::vector<cap_msg_field *> &cap_message::get_fields() const {
    return fields;
}

const std::string &cap_message::getSymbol() const {
    return symbol;
}

char cap_message::getDelim() const {
    return delim;
}

void cap_message::setDelim(char delim) {
    cap_message::delim = delim;
}






