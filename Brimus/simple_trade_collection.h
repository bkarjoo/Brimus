//
// Created by b.karjoo on 5/3/2017.
//

#ifndef BRIMUS_SIMPLE_TRADE_COLLECTION_H
#define BRIMUS_SIMPLE_TRADE_COLLECTION_H

#include "stdafx.h"
#include "simple_trade.h"

class simple_trade_collection {
    std::vector<std::shared_ptr<simple_trade>> open_trades;
    std::vector<std::shared_ptr<simple_trade>> closed_trades;

public:
};


#endif //BRIMUS_SIMPLE_TRADE_COLLECTION_H
