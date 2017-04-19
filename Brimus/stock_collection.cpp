//
// Created by b.karjoo on 4/17/2017.
//

#include "stock_collection.h"
#include "strategy_symbol_basket.h"

using namespace std;



void stock_collection::on_message(const cap_message &message) {
    stocks[message.getSymbol()]->tick_update(message);
}

bool stock_collection::has_instrument(const string &symbol) {
    auto s = stocks.find(symbol);
    return (s == stocks.end());
}

void stock_collection::add_basket(const strategy_symbol_basket & basket,
     function<void(const stock_collection::ptime &, const string &, stock_field, double)> callback) {
    auto& symbols = basket.getSymbols();
    for (auto& a : symbols)
        add_stock(a, callback);
}

void stock_collection::add_stock(const string & symbol,
     function<void(const stock_collection::ptime &, const string &, stock_field, double)> callback) {
    auto& stk = add_stock(symbol);
    stk.add_observer(callback);
}

stock &stock_collection::add_stock(string symbol) {
    auto s = stocks.find(symbol);
    if (s == stocks.end()) {
        stocks[symbol]  = make_shared<stock>(symbol);
        return *stocks[symbol];
    } else {
        return *s->second;
    }
}

shared_ptr<stock> stock_collection::get_stock(const std::string &symbol) {
    auto s = stocks.find(symbol);
    if (s == stocks.end()) {
        return nullptr;
    } else {
        return s->second;
    }
}

double stock_collection::AskPrice(const std::string &symbol) {
    auto stk = get_stock(symbol);
    if (stk) return stk->getAsk(); else return 0;
}

double stock_collection::BidPrice(const std::string &symbol) {
    auto stk = get_stock(symbol);
    if (stk) return stk->getBid(); else return 0;
}

double stock_collection::LastPrice(const std::string &symbol) {
    auto stk = get_stock(symbol);
    if (stk) return stk->getLast(); else return 0;
}
