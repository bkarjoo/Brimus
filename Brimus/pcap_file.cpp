//
// Created by b.karjoo on 3/20/2017.
//

#include "pcap_file.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::shared_ptr;

void pcap_file::run(const std::vector<std::string> &file_paths) {

    // TODO : get the dates from a launch_rule class
    // TODO : get the symbols from a symbol class

    for (auto& a : file_paths) {
        ifstream fs(a);
        char c;
        char prev = 0;

        char field_code = 0;
        char field_exchange = 0;
        string field_code_val = "";
        string field_val = "";
        string packet_header_str;
        string symbol = "";
        char msg_delim = 0;
        char prefix = 0;

        // used for packet time
        string hours_str, minutes_str, seconds_str;
        int hours = 0, minutes = 0, seconds = 0, time_since_midnight = 0;
        bool packet_header_has_time = false;

        shared_ptr<st_message> msg_ptr = nullptr;

        while (fs.get(c)) {
            //cout << c << endl;
            // first check if it's a delimiter starting with field delimiter which occurs the most
            if (mode != read_mode::IGNORE_MSG
                && mode != read_mode::IGNORE_PACKET
                && mode != read_mode::PACKET_HEADER
                && is_field_delimiter(c, prev)) {

                if (mode == read_mode::FIELD) {
                    // one field completed starting a new field
                        msg_ptr->add_field(field_code, field_code_val, field_val, field_exchange);
                } else if (mode == read_mode::MSG_HEADER) {
                    // message header completed and starting first field
                    if (symbols.find(symbol) != symbols.end()) {
                        msg_ptr = std::make_shared<st_message>(c);
                        if (!prefix == 0) msg_ptr->set_prefix(prefix);
                        msg_ptr->set_symbol(symbol);
                        mode = read_mode::FIELD;
                    } else {
                        mode = read_mode::IGNORE_MSG;
                        msg_ptr = nullptr;
                    }
                    prefix = 0;
                    symbol = "";

                }
                // reset and initialize field variables
                field_code_val = ""; field_val = ""; field_exchange = 0;
                field_code = c;
            } else if (mode != read_mode::MSG_HEADER
                       && mode != read_mode::IGNORE_PACKET
                       && is_msg_delimiter(c, prev)) {

                if (mode == read_mode::FIELD) {
                    // last field of previous message complete
                    msg_ptr->add_field(field_code,field_code_val,field_val,field_exchange);
                    if (is_upper_case(c)) symbol += c; else msg_delim = c;
                    mode = read_mode::MSG_HEADER;
                } else if (mode == read_mode::PACKET_HEADER) {
                    // packet header complete, new message starting
//                    cout << endl;
//                    cout << "Packet header complete: " << packet_header_str << endl;
                    if (packet_header_has_time) {
                        try {
                            hours = stoi(hours_str);
                            minutes = stoi(minutes_str);
                            seconds = stoi(seconds_str);
                            time_since_midnight = (((hours * 60) + minutes) * 60) + seconds;
                            if (time_since_midnight < start_time_seconds ||
                                time_since_midnight > end_time_seconds)
                                mode = read_mode::IGNORE_PACKET;
                            else {
                                //cout << packet_header_str << endl;
                                if (is_upper_case(c)) symbol += c; else msg_delim = c;
                                mode = read_mode::MSG_HEADER;
                            }
                        } catch (...) {
                            cout << "error: time capture was off in packet header" << endl;
                        }
                    } else {
                        if (is_upper_case(c)) symbol += c; else msg_delim = c;
                        mode = read_mode::MSG_HEADER;
                    }
                } else {
                    if (is_upper_case(c)) symbol += c; else msg_delim = c;
                    mode = read_mode::MSG_HEADER;
                }

                // TODO: send completed message to observers

                if (msg_ptr != nullptr) {
                    notifier->notify(msg_ptr);
                    msg_ptr = nullptr;
                }

                // create a new message



            } else if (mode != read_mode::MSG_HEADER
                       && is_packet_delimiter(c)) {

                // last field of previous message was read
                if (mode == read_mode::FIELD) {
                    msg_ptr->add_field(field_code,field_code_val,field_val,field_exchange);
                }

                packet_header_str = "";
                hours_str = "", minutes_str = ""; seconds_str = "";
                packet_header_has_time = false;
                mode = read_mode::PACKET_HEADER;

            } else if (mode == read_mode::FIELD) {


                if (c == ',')
                    std::swap(field_val,field_code_val);
                else if (is_lower_case(c))
                    field_exchange = c;
                else
                    field_val += c;

            } else if (mode == read_mode::MSG_HEADER) {

                if (symbol.length() == 0 && is_lower_case(c))
                    prefix = c;
                else
                    symbol += c;

            } else if (mode == read_mode::PACKET_HEADER) {

                packet_header_str += c;
                if (packet_header_str.length() < 3) hours_str += c;
                if (packet_header_str.length() > 3 && packet_header_str.length() < 6)
                    minutes_str += c;
                if (packet_header_str.length() > 6 && packet_header_str.length() < 9)
                    seconds_str += c;
                if (c == ':') packet_header_has_time = true;

            }
            prev = c;
        }
        if (msg_ptr != nullptr) {
            msg_ptr->add_field(field_code,field_code_val,field_val,field_exchange);
            notifier->notify(msg_ptr);
            msg_ptr = nullptr;
        }
        fs.close();

    }
}


std::string pcap_file::get_full_path(std::string date, std::string symbol) {
    /* QUESTION : where do I get the file from?
 * ANSWER: from the E: drive
 * QUESTION : how do I know this?
 * ANSWER: it's hardcoded / or it's given to me in configuration file
 */
    // TODO : the path is hard coded for now, however it should be set in config file
    string path = "E:\\";
    /* QUESTION : how do I know which file I get?
     * ANSWER: in E: you have folders with years, 2016, 2017, etc . . .
     * you may also have more drives later . . .
     * in the year folders you have 12 month folders 01, 02, .. , 12
     * in the month folder you have a folder for each day 1, 2, .. , (last day of month)
     * in the day folders there's is a CAP file for each symbol
     * you will load the symbol files that you need, up to 2045 of them
     * then you'll sync them by reading one message from each then taking lowest seq #
     * then you get the next message from the file whose message was used and so forth
     * the dates themselves are provided by the strategy's launch rule definition
     */
    // TODO : get the date_ptr from date_ptr param
    // not that it can be passed as 2017-1-1 from launch rule def?
    string year_str = "2017";
    string month_str = "01";
    string day_str = "31";
    /* Question : how do I know which file I use?
     * ANSWER : the file is provided by the strategy's global_basket definition
     */
    return path + year_str + "\\" + month_str + "\\"
           + day_str + "\\" + symbol + ".CAP";
}

bool pcap_file::is_packet_delimiter(const char &c) {
    return c == 31;
}

/*
 * messages can be delimited by char 11, 13, 14, or 15
 * however occasionally these delimiters are missing
 * in such cases an uppercase letter (a symbol) starts the message
 * sometimes this uppercase letter is preceded by a lowercase letter (exchange code)
 */
bool pcap_file::is_msg_delimiter(const char &c, const char &prev) {
    return ( c == 11 || c == 13 || c == 14 || c == 15 )
           || ( is_upper_case(c) && !is_upper_case(prev) && prev != ',' );
}

bool pcap_file::is_upper_case(const char &c) {
    return c >= 65 && c <= 90;
}

bool pcap_file::is_field_delimiter(const char &c, const char &prev) {
    return is_lower_case(c) && !is_lower_case(prev)
           && (!is_packet_delimiter(prev))
           && (!( prev == 11 || prev == 13 || prev == 14 || prev == 15 ));
}

bool pcap_file::is_lower_case(const char &c) {
    return c >= 97 && c <=122;
}



int pcap_file::getStart_time_seconds() const {
    return start_time_seconds;
}

void pcap_file::setStart_time_seconds(int start_time_seconds) {
    pcap_file::start_time_seconds = start_time_seconds;
}

int pcap_file::getEnd_time_seconds() const {
    return end_time_seconds;
}

void pcap_file::setEnd_time_seconds(int end_time_seconds) {
    pcap_file::end_time_seconds = end_time_seconds;
}

void pcap_file::add_instrument(std::string symb) {
    notifier->add_instrument(symb);
    symbols.insert(symb);
}

void pcap_file::add_instrument(std::shared_ptr<instrument> i) {
    notifier->add_instrument(i);
    symbols.insert(i->getSymbol());
}

pcap_file &pcap_file::get_instance() {
    static pcap_file pf;
    return pf;
}



