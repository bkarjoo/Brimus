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
        stock_collection::get_instance().on_packet_time(p);

    } catch (...) {

    }
}

boost::posix_time::ptime message_router::convert_time(std::string header) {
    const std::locale loc = std::locale(std::locale::classic(), new boost::posix_time::time_input_facet("%H:%M:%S %m/%d/%Y"));
    std::istringstream is(header);
    is.imbue(loc);

    boost::posix_time::ptime t;
    is >> t;
    return t;
}
