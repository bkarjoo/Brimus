//
// Created by b.karjoo on 3/30/2017.
//

#include "symbol_basket.h"

void symbol_basket::add_symbol(const std::string &symbol) {
    symbols.insert(symbol);
}

int symbol_basket::get_symbol_count() {
    return symbols.size();
}

const std::set<std::string> &symbol_basket::getSymbols() const {
    return symbols;
}


