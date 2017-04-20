//
// Created by Behrooz Karjoo on 4/15/17.
//

#include "cap_file_reader.h"
#include "stock_collection.h"
// #include "global_basket.h"
// IMessageReceiver

using namespace std;

int cap_file_reader::getStart_time_seconds() const {
    return start_time_seconds;
}

void cap_file_reader::setStart_time_seconds(int start_time_seconds) {
    cap_file_reader::start_time_seconds = start_time_seconds;
}

int cap_file_reader::getEnd_time_seconds() const {
    return end_time_seconds;
}

void cap_file_reader::setEnd_time_seconds(int end_time_seconds) {
    cap_file_reader::end_time_seconds = end_time_seconds;
}

void cap_file_reader::run(const std::vector<std::string> &file_paths) {

    // TODO : get the dates from a launch_rule class
    // TODO : get the symbols from a symbol class

    for (auto& a : file_paths) {
        //global_basket& gb = global_basket::get_instance();
        //boost::optional<instrument&> instr = {};
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

        unique_ptr<cap_message> msg_ptr = nullptr;

        while (fs.get(c)) {
            //cout << c << endl;
            // first check if it's a delimiter starting with field delimiter which occurs the most
            if (mode != capfile_read_mode::IGNORE_MSG
                && mode != capfile_read_mode::IGNORE_PACKET
                && mode != capfile_read_mode::PACKET_HEADER
                && is_field_delimiter(c, prev)) {

                if (mode == capfile_read_mode::FIELD) {
                    // one field completed starting a new field
                    msg_ptr->add_field(field_code, field_code_val, field_val, field_exchange);
                } else if (mode == capfile_read_mode::MSG_HEADER) {
                    // message header completed and starting first field
                    //instr = gb.get_instrument(symbol);

                    if (imr->has_instrument(symbol)) {
                        msg_ptr = std::make_unique<cap_message>(c);
                        if (!prefix == 0) msg_ptr->set_prefix(prefix);
                        msg_ptr->set_symbol(symbol);
                        mode = capfile_read_mode::FIELD;
                    } else {
                        mode = capfile_read_mode::IGNORE_MSG;
                        msg_ptr = nullptr;
                    }
                    prefix = 0;
                    symbol = "";

                }
                // reset and initialize field variables
                field_code_val = ""; field_val = ""; field_exchange = 0;
                field_code = c;
            } else if (mode != capfile_read_mode::MSG_HEADER
                       && mode != capfile_read_mode::IGNORE_PACKET
                       && is_msg_delimiter(c, prev)) {

                if (mode == capfile_read_mode::FIELD) {
                    // last field of previous message complete
                    msg_ptr->add_field(field_code,field_code_val,field_val,field_exchange);
                    if (is_upper_case(c)) symbol += c; else msg_delim = c;
                    mode = capfile_read_mode::MSG_HEADER;
                } else if (mode == capfile_read_mode::PACKET_HEADER) {
                    // packet header complete, new message starting
                    cout << endl;
                    cout << "Packet header complete: " << packet_header_str << endl;
                        imr->on_packet_header(packet_header_str);
                    if (packet_header_has_time) {
                        try {
                            hours = stoi(hours_str);
                            minutes = stoi(minutes_str);
                            seconds = stoi(seconds_str);
                            time_since_midnight = (((hours * 60) + minutes) * 60) + seconds;
                            if (time_since_midnight < start_time_seconds ||
                                time_since_midnight > end_time_seconds)
                                mode = capfile_read_mode::IGNORE_PACKET;
                            else {
                                //cout << packet_header_str << endl;
                                if (is_upper_case(c)) symbol += c; else msg_delim = c;
                                mode = capfile_read_mode::MSG_HEADER;
                            }
                        } catch (...) {
                            cout << "error: time capture was off in packet header" << endl;
                        }
                    } else {
                        if (is_upper_case(c)) symbol += c; else msg_delim = c;
                        mode = capfile_read_mode::MSG_HEADER;
                    }
                } else {
                    if (is_upper_case(c)) symbol += c; else msg_delim = c;
                    mode = capfile_read_mode::MSG_HEADER;
                }

                // TODO: send completed message to observers

                if (msg_ptr) {
                    if (imr)
                        imr->on_message(*msg_ptr);
                    else
                        stock_collection::get_instance().on_message(*msg_ptr);
                    //instr->on_message(move(msg_ptr));
                    msg_ptr = nullptr;
                }

                // create a new message



            } else if (mode != capfile_read_mode::MSG_HEADER
                       && is_packet_delimiter(c)) {

                // last field of previous message was read
                if (mode == capfile_read_mode::FIELD) {
                    msg_ptr->add_field(field_code,field_code_val,field_val,field_exchange);
                }

                packet_header_str = "";
                hours_str = "", minutes_str = ""; seconds_str = "";
                packet_header_has_time = false;
                mode = capfile_read_mode::PACKET_HEADER;

            } else if (mode == capfile_read_mode::FIELD) {


                if (c == ',')
                    std::swap(field_val,field_code_val);
                else if (is_lower_case(c))
                    field_exchange = c;
                else
                    field_val += c;

            } else if (mode == capfile_read_mode::MSG_HEADER) {

                if (symbol.length() == 0 && is_lower_case(c))
                    prefix = c;
                else
                    symbol += c;

            } else if (mode == capfile_read_mode::PACKET_HEADER) {

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
            // TODO : write to interface
            if (imr)
                imr->on_message(*msg_ptr);
            else
                stock_collection::get_instance().on_message(*msg_ptr);

            // instr->on_message(move(msg_ptr));
            msg_ptr = nullptr;
        }
        fs.close();

    }
}


bool cap_file_reader::is_packet_delimiter(const char &c) {
    return c == 31;
}

/*
 * messages can be delimited by char 11, 13, 14, or 15
 * however occasionally these delimiters are missing
 * in such cases an uppercase letter (a symbol) starts the message
 * sometimes this uppercase letter is preceded by a lowercase letter (exchange code)
 */
bool cap_file_reader::is_msg_delimiter(const char &c, const char &prev) {
    return ( c == 11 || c == 13 || c == 14 || c == 15 )
           || ( is_upper_case(c) && !is_upper_case(prev) && prev != ',' );
}

bool cap_file_reader::is_upper_case(const char &c) {
    return c >= 65 && c <= 90;
}

bool cap_file_reader::is_field_delimiter(const char &c, const char &prev) {
    return is_lower_case(c) && !is_lower_case(prev)
           && (!is_packet_delimiter(prev))
           && (!( prev == 11 || prev == 13 || prev == 14 || prev == 15 ));
}

bool cap_file_reader::is_lower_case(const char &c) {
    return c >= 97 && c <=122;
}

void cap_file_reader::setImr(std::unique_ptr<IMessageReceiver> unique_imr) {
    imr = move(unique_imr);
}








