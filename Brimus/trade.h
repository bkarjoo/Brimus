//
// Created by b.karjoo on 5/2/2017.
//

#ifndef BRIMUS_TRADE_H
#define BRIMUS_TRADE_H
#include "stdafx.h"
#include "execution.h"

class trade {
    std::vector<execution> entries;
    std::vector<execution> exits;
public:
    void add_entry(std::shared_ptr<execution>);
    void add_exit(std::shared_ptr<execution>);
};


#endif //BRIMUS_TRADE_H
