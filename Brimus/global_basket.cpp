//
// Created by b.karjoo on 3/28/2017.
//

#include "global_basket.h"

instrument & global_basket::add_instrument(std::string symbol) {
    if (instruments.find(symbol) == instruments.end()) {
        instruments[symbol] = std::make_unique<instrument>(symbol);
        instruments[symbol]->PropertyChanged.connect(
                [this](instrument &i, const std::string &property_name) {
                    auto &ov = observers[property_name];
                    for (auto a: ov) a(property_name);
                }
        );
    }
    return *instruments[symbol];
}

void global_basket:: add_basket(const std::shared_ptr<symbol_basket> symbols,
                               std::function<void(std::string)> callback) {
    // get the symbols from the basket and turn them into instruments
    auto& capFileReader = pcap_file::get_instance();
    auto& symbs = symbols->getSymbols();
    for (auto& a : symbs) {
        add_instrument(a);
        symbol_observer(a, callback);
    }
}

void global_basket::symbol_observer(std::string symbol, std::function<void(std::string)> symbol_changed_callback) {
    observers[symbol].push_back(symbol_changed_callback);
}

boost::optional<instrument &> global_basket::get_instrument(std::string symbol) {
    if (instruments.find(symbol) != instruments.end())
        return *instruments[symbol];
    else
        return {};
}




