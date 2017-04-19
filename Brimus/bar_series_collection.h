//
// Created by b.karjoo on 4/19/2017.
//

#ifndef BRIMUS_BAR_SERIES_COLLECTION_H
#define BRIMUS_BAR_SERIES_COLLECTION_H

#include "stdafx.h"
#include "bar_series.h"

class bar_series_collection {
    bar_series_collection() {};
    ~bar_series_collection() {};
    std::map<std::string,bar_series> collection;
public:
    bar_series_collection(bar_series_collection const&) = delete;
    void operator=(bar_series_collection const&) = delete;
    static bar_series_collection& get_instance() {
        static bar_series_collection bsc;
        return bsc;
    }
    void add_bar_series(std::string symbol, int duration,
        std::function<void(const bar_series&)>);
};


#endif //BRIMUS_BAR_SERIES_COLLECTION_H
