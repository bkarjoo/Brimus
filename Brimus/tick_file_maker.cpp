//
// Created by b.karjoo on 4/4/2017.
//

#include "tick_file_maker.h"




using namespace std;

const std::string &tick_file_maker::getOutput_path() const {
    return output_path;
}

void tick_file_maker::setOutput_path(const std::string &output_path) {
    tick_file_maker::output_path = output_path;
}

void tick_file_maker::on_message(const cap_message &message) {
    std::string s;
    s += message.getPrefix();
    s += message.getSymbol();
    int precision = 4;
    bool field_encountered = false;
    for (auto a : message.get_fields()) {
        if (
        (a->field_code == 'f' && a->field_code_value != "")
        || a->field_code == 't'
 //       || a->field_code == 'j'
 //       || a->field_code == 'k'
        || a->field_code == 'b'
        || a->field_code == 'a'
        || a->field_code == 'o') {
            if (a->field_code == 'f') {
                try {
                    precision = stoi(a->field_value);
                } catch (...) {}
            } else {
                if (is_dup(message.getSymbol(),a->field_code, a->field_value)) continue;
                add_dup_tracker(message.getSymbol(),a->field_code, a->field_value);
                field_encountered = true;
                s += a->field_code;
                if (a->field_exchange != 0) s += a->field_exchange;
                if (a->field_code_value != "") {
                    s += a->field_code_value;
                    s += ',';
                }
                if (a->field_code == 't'
                    || a->field_code == 'b'
                    || a->field_code == 'a') {
                    s += format_price(precision, a->field_value);
                } else {
                    s += a->field_value;
                }
            }
        }
    }
    if (field_encountered) {
        *os << s;
        //std::cout << s;
        //char a;
        //cin >> a;
    }

}

bool tick_file_maker::has_instrument(const std::string & symbol) {
    //return symbol_list.find(symbol) != symbol_list.end();
    return true;
}

std::string tick_file_maker::format_price(int precision, const string &price) {
    // TODO convert price into an integer
    try {
        double d = stod(price);
        double answer = d / pow(static_cast<double>(10),static_cast<double>(precision));
        return to_str(answer);
    } catch (...) {
        return "";
    }
}

void tick_file_maker::on_packet_header(const std::string &pheader) {
    dups.clear();
    *os << pheader;

}

void tick_file_maker::add_dup_tracker(std::string symbol, char field, std::string value) {
    auto it = dups.find(symbol);
    if (it == dups.end())
        dups.insert(make_pair(symbol, dup_tracking(symbol, field, value)));
    else
    {
        it->second.f = field;
        it->second.v = value;
    }
}

bool tick_file_maker::is_dup(std::string symbol, char field, std::string value) {
    auto it = dups.find(symbol);
    if (it == dups.end()) return false;
    return (it->second.f == field && it->second.v == value);
}
