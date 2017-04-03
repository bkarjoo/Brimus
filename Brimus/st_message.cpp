//
// Created by b.karjoo on 3/21/2017.
//


#include "st_message.h"


void st_message::add_field(const char &fCode, std::string &fCodeVal, std::string &fVal, const char &fExch) {
    st_field* f = new st_field();
    f->field_code = fCode;
    std::swap(f->field_code_value,fCodeVal);
    std::swap(f->field_value,fVal);
    if (fExch != 0) f->field_exchange = fExch;
    fields.push_back(f);
}

st_message::st_message(char pfix, std::string &symb) {
    prefix = pfix;
    std::swap(symb,symbol);
}

std::string st_message::to_string() {
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

st_message::st_message(char dlim) {
    delim = dlim;
}

void st_message::set_prefix(const char &c) {
    prefix = c;
}

void st_message::set_symbol(std::string &symb) {
    std::swap(symb,symbol);
}

const std::vector<st_field *> &st_message::get_fields() const {
    return fields;
}

const std::string &st_message::getSymbol() const {
    return symbol;
}

char st_message::getDelim() const {
    return delim;
}

void st_message::setDelim(char delim) {
    st_message::delim = delim;
}






