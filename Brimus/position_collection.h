//
// Created by b.karjoo on 4/7/2017.
//

#ifndef BRIMUS_POSITION_COLLECTION_H
#define BRIMUS_POSITION_COLLECTION_H


#include "stdafx.h"
#include "position.h"

class position_collection { 
    typedef std::map<std::string, position> position_map;
    position_map positions;
public:
    void add_position(std::string symbol, int qty);
    int get_position(std::string symbol) const;
    bool has_position(std::string symbol) const { return get_position(symbol) != 0; }
    void bought(std::string symbol,  int qty);
    void sold(std::string symbol,  int qty);
};


#endif //BRIMUS_POSITION_COLLECTION_H
