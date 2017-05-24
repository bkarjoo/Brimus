//
// Created by b.karjoo on 4/17/2017.
//

#include "message_router.h"
#include "stock_collection.h"
using namespace std;

message_router::message_router() {
}

void message_router::on_message(const cap_message &message) {
    stock_collection::get_instance().on_message(message);
}

bool message_router::has_instrument(const std::string &symbol) {
    return stock_collection::get_instance().has_instrument(symbol);
}

void message_router::on_packet_header(const std::string &header) {
    try {
        boost::posix_time::ptime p = convert_time(header);
        std::string s = mock_time_stamp(header);
        stock_collection::get_instance().on_packet_time(p);
        stock_collection::get_instance().set_mock_time(s);

    } catch (...) {

    }
}

boost::posix_time::ptime message_router::convert_time(std::string header) {
    const std::locale loc = std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%H:%M:%S %m/%d/%Y"));
    std::istringstream is(header);
    is.imbue(loc);
    boost::posix_time::ptime t;
    is >> t;
    if (t.is_not_a_date_time()) {
        const std::locale loc2 = std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%H:%M %m/%d/%Y"));
        std::istringstream vs(header);
        vs.imbue(loc2);
        boost::posix_time::ptime c;
        vs >> c;
        return c;
    }
    return t;
}

std::string message_router::mock_time_stamp(const std::string &s) {
    if (s.length() < 8) return "";
    if (s[2] != ':') return "";
    string hr_str = ""; if (s[0] != '0') hr_str += s[0]; hr_str += s[1];
    string m_str = ""; m_str += s[3]; m_str += s[4];
    string s_str = ""; s_str += s[6]; s_str += s[7];
    string ms = "000";
    return hr_str + m_str + s_str + ms;
}
