//
// Created by b.karjoo on 4/19/2017.
//

#include "bar_series_collection.h"
#include "stock_collection.h"

using namespace std;

void bar_series_collection::add_bar_series(std::string symbol, int duration,
    function<void(const bar_series&)> callback) {
    unique_ptr<bar_series> bs = make_unique<bar_series>(symbol);
    bs->setBar_duration(duration);
    stock_collection& sc = stock_collection::get_instance();
    sc.add_stock(symbol,bs->get_callback());
    bs->AddNewBarObserver(callback);
}
