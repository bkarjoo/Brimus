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
    /// eliminate trace messages
    if (message.getSymbol().substr(0,3) == ".TR") return;

    // start a new message header if symbol changed
    // previous symbol resets on new packet header
    if (message.getSymbol() != previous_symbol) {
        if (message.getPrefix() != 0) s += message.getPrefix();
        s += message.getSymbol();
        previous_symbol = message.getSymbol();
    }

    int precision = 4;
    bool field_encountered = false;

    for (auto a : message.get_fields()) {
        if (
        (a->field_code == 'f' && a->field_code_value != "")
        || a->field_code == 't'
        || a->field_code == 'i'
        //|| a->field_code == 'j' // bid size
        //|| a->field_code == 'k' // ask size
        || a->field_code == 'b'
        || a->field_code == 'a'
        || a->field_code == 'o') {
            if (a->field_code == 'f') {
                try {
                    // set the precision
                    // summary file will include decimals and no precision factor
                    precision = stoi(a->field_value);
                } catch (...) {}
            } else {
                // if any field except trade size is reported twice will not be recorded
                if (is_dup(message.getSymbol(),a->field_code, a->field_value)) continue;

                // new field is given to dup tracker
                add_dup_tracker(message.getSymbol(),a->field_code, a->field_value);

                // only if there's a field we need with the symbol will it be rcorded
                field_encountered = true;
                s += a->field_code;
                if (a->field_exchange != 0) s += a->field_exchange;
                if (a->field_code_value != "") {
                    s += a->field_code_value;
                    s += ',';
                }
                // record the value (format if it's price)
                if (a->field_code == 't'
                    || a->field_code == 'b'
                    || a->field_code == 'a'
                    || a->field_code == 'o') {
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
    // we record all instruments
    return  true;
}

std::string tick_file_maker::format_price(int precision, const string &price) {
    try {
        double d = stod(price);
        double answer = d / pow(static_cast<double>(10),static_cast<double>(precision));
        return to_str(answer);
    } catch (...) {
        return "";
    }
}

void tick_file_maker::on_packet_header(const std::string &pheader) {
    if (pheader.length() < 3) return;
    if (pheader[2] != ':') return;
    string hour = "";
    hour += pheader[0]; hour += pheader[1];
    try {
        int h = stoi(hour);
        if (h < 4 || h > 19) return;
    } catch (...) {
        return;
    }

    dups.clear();
    previous_symbol = "";
    char delimiter = 31;
    *os << delimiter;
    *os << pheader;

}

void tick_file_maker::add_dup_tracker(std::string symbol, char field, std::string value) {
    map<string,dup_tracking>* m = nullptr;
    switch (field) {
        case 'a':
            m = &lastAsk;
            break;
        case 'b':
            m = &lastBid;
            break;
        case 't':
            m = &lastLast;
            break;
        case 'j':
            m = &lastBidSize;
            break;
        case 'k':
            m = &lastAskSize;
            break;
            // not recording i because duplicated count in calculating vol
    }
    if (!m) return;
    auto it = m->find(symbol);
    if (it == m->end())
        m->insert(make_pair(symbol, dup_tracking(symbol, value)));
    else
    {
        it->second.v = value;
    }
}

bool tick_file_maker::is_dup(std::string symbol, char field, std::string value) {
    map<string,dup_tracking>* m = nullptr;
    switch (field) {
        case 'a':
            m = &lastAsk;
            break;
        case 'b':
            m = &lastBid;
            break;
        case 't':
            m = &lastLast;
            break;
        case 'j':
            m = &lastBidSize;
            break;
        case 'k':
            m = &lastAskSize;
            break;
            // not recording i because duplicated count in calculating vol
    }
    if (!m) return false;
    auto it = m->find(symbol);
    if (it == m->end()) return false;
    return it->second.v == value;
}
