//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_SYMBOL_BASKET_H
#define BRIMUS_SYMBOL_BASKET_H

#include "stdafx.h"
#include "strategy_launch_rules.h"

class strategy_symbol_basket {
public:
    void add_symbol(const std::string &symbol);
    int get_symbol_count();
    const std::set<std::string> &getSymbols() const;
private:
    std::set<std::string> symbols;
};


#endif //BRIMUS_SYMBOL_BASKET_H


