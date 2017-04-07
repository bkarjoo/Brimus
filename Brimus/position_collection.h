//
// Created by b.karjoo on 4/7/2017.
//

#ifndef BRIMUS_POSITION_COLLECTION_H
#define BRIMUS_POSITION_COLLECTION_H


#include <memory>
#include <map>
#include "position.h"

class position_collection {
    typedef std::map<std::string, std::shared_ptr<position>> position_map;
    position_map positions;
public:
    void add_position(std::string symbol, int qty);
    int get_position(std::string symbol);
    bool has_position(std::string symbol) { return get_position(symbol) != 0; }
};


#endif //BRIMUS_POSITION_COLLECTION_H
