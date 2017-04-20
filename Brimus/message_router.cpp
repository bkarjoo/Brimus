//
// Created by b.karjoo on 4/17/2017.
//

#include "message_router.h"
#include "stock_collection.h"

message_router::message_router() {
}

void message_router::on_message(const cap_message &message) {
    stock_collection::get_instance().on_message(message);
}

bool message_router::has_instrument(const std::string &symbol) {
    return stock_collection::get_instance().has_instrument(symbol);
}

void message_router::on_packet_header(const std::string &string) {

}
