//
// Created by b.karjoo on 4/19/2017.
//

#include "S_SpyArt_Factory.h"
#include "strategy_launch_rules.h"
#include "strategy_symbol_basket.h"
#include "stock_collection.h"
#include "bar_series_collection.h"
#include "S_SpyArt.h"

using namespace std;

// Needs one stock SPY for the basket - will reside in stock_collection
// Needs a 5 minute bar series - will reside in static bar_series_collection
// Launch rules just one day - its path must be passed to the strategies run func
unique_ptr<strategy> S_SpyArt_Factory::get_strat() {
    unique_ptr<strategy_launch_rules> lr = make_unique<strategy_launch_rules>();
    lr->add_date(2017,01,03); // must be loaded from a file
    unique_ptr<strategy_symbol_basket> sb = make_unique<strategy_symbol_basket>();
    sb->add_symbol("SPY"); // must be loaded from a file
    unique_ptr<strategy> s = make_unique<strategy>(move(lr),move(sb));
    stock_collection& sc = stock_collection::get_instance();
    // strategy is connected with the symbols
    sc.add_basket(s->getSymbolBasket(),s->get_update_symbol_callback());

    bar_series_collection& bsc = bar_series_collection::get_instance();
    // add a bar series for every symbol in the strategy, in this case 1
    bsc.add_bar_series("SPY",5,s->get_update_bar_series_callback());
    s->setRules(make_unique<S_SpyArt>());
    return move(s);

}
