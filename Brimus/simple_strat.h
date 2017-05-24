//
// Created by b.karjoo on 5/2/2017.
//

#ifndef BRIMUS_SIMPLE_STRAT_H
#define BRIMUS_SIMPLE_STRAT_H
#include "stdafx.h"
#include "stock.h"
#include "simple_bar.h"

class simple_strat {
    simple_bar* bar_array[8];
public:
    std::function<void(const stock&,stock_field)> get_callback();

    void check_rules(const stock &stock, stock_field field);

    void update_bars(double last, const boost::posix_time::ptime &ptime);

    void create_new_bar(double last, const boost::posix_time::ptime &ptime);
};


#endif //BRIMUS_SIMPLE_STRAT_H
