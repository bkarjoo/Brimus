//
// Created by b.karjoo on 5/2/2017.
//

#include "simple_strat.h"
using namespace std;
std::function<void(const stock &, stock_field)> simple_strat::get_callback() {
    return [this](const stock& stk, stock_field sf) {
            if (sf == stock_field::LAST && stk.Last() != 0)
                check_rules(stk, sf);
            };
}

void simple_strat::check_rules(const stock &s, stock_field f) {
    // update indicators (8 5 min bars needed)
    update_bars(s.Last(), s.Time());
}

void simple_strat::update_bars(double last, const boost::posix_time::ptime &ptime) {
    if (bar_array[7]) {
        int start_minute = bar_array[7]->getStartTime().time_of_day().minutes();
        int now_minute = ptime.time_of_day().minutes();
        if (now_minute == (start_minute == 55 ? 0 : start_minute + 5))
            create_new_bar(last, ptime);
        else
            bar_array[7]->add_price(last);
    } else
        create_new_bar(last, ptime);


}

void simple_strat::create_new_bar(double last, const boost::posix_time::ptime &ptime) {
    if (bar_array[0]) delete bar_array[0];
    for (int i = 0; i < 7; i++)
        bar_array[i] = bar_array[i+1];
    bar_array[7] = new simple_bar(ptime, last);
    if (bar_array[6]) cout << *bar_array[6] << endl;
}




