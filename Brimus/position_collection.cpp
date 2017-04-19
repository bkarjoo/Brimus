//
// Created by b.karjoo on 4/7/2017.
//

#include "position_collection.h"

 void position_collection::add_position(std::string symbol, int qty) {
    auto it = positions.find(symbol);
    if (it == positions.end()) {
        positions[symbol] = position(qty);
    } else {
        (positions[symbol]) += qty;
    }
}

int position_collection::get_position(std::string symbol) const {
    auto it = positions.find(symbol);
    if (it != positions.end()) {
        return it->second.get_position();
    } else {
        return 0;
    }
}

void position_collection::bought(std::string symbol,  int qty) {
    add_position(symbol, abs(qty));
}

void position_collection::sold(std::string symbol,  int qty) {
    add_position(symbol, -abs(qty));
}



