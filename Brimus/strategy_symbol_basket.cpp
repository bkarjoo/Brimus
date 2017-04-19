//
// Created by b.karjoo on 3/30/2017.
//

#include "strategy_symbol_basket.h"

void strategy_symbol_basket::add_symbol(const std::string &symbol) {
    symbols.insert(symbol);
}

int strategy_symbol_basket::get_symbol_count() {
    return symbols.size();
}

const std::set<std::string> &strategy_symbol_basket::getSymbols() const {
    return symbols;
}


