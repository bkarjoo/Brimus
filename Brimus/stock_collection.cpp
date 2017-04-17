//
// Created by b.karjoo on 4/17/2017.
//

#include "stock_collection.h"
#include "symbol_basket.h"

using namespace std;

stock &stock_collection::add_stock(std::string symbol) {
    auto s = stocks.find(symbol);
    if (s == stocks.end()) {
        stock& s = stocks[symbol];
        s.setSymbol(symbol);
    } else {
        return s->second;
    }
}

void stock_collection::on_message(const st_message &message) {
    stocks[message.getSymbol()].tick_update(message);
}

bool stock_collection::has_instrument(const std::string &symbol) {
    auto s = stocks.find(symbol);
    return (s == stocks.end());
}

void stock_collection::add_basket(const symbol_basket & basket,
                                  std::function<void(const stock_collection::ptime &, const std::string &, stock_field,
                                                     double)> callback) {
    const set<string>& symbols = basket.getSymbols();
    cout << symbols.size() << endl;
    for (const string& a : symbols)
    {
        auto s = stocks.find(a);
        if (s == stocks.end()) {
            auto& stk = add_stock(a);
            stk.add_observer(callback);
        } else {
            s->second.add_observer(callback);
        }
    }
}
