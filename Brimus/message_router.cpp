//
// Created by b.karjoo on 4/17/2017.
//

#include "message_router.h"
#include "stock_collection.h"

message_router::message_router() {
    sc = stock_collection::get_instance();
}

void message_router::on_message(const st_message &message) {
    sc->on_message(message);
}

bool message_router::has_instrument(const std::string &symbol) {
    return sc->has_instrument(symbol);
}
