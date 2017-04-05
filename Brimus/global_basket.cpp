//
// Created by b.karjoo on 3/28/2017.
//

#include "global_basket.h"

std::shared_ptr<instrument> global_basket::add_instrument(std::string symbol) {
    if (instruments.find(symbol) == instruments.end())  {
        instruments[symbol] = std::make_shared<instrument>(symbol);
        instruments[symbol]->PropertyChanged.connect(
                [this](instrument& i, const std::string& property_name)
                {
                    auto& ov = observers[property_name];
                    for (auto a: ov) a(property_name);
                }
        );
        return instruments[symbol];
    }
    return nullptr;
}

void global_basket::add_basket(const std::shared_ptr<symbol_basket> symbols,
                               std::function<void(std::string)> callback) {
    // get the symbols from the basket and turn them into instruments
    auto& capFileReader = pcap_file::get_instance();
    auto& symbs = symbols->getSymbols();
    for (auto& a : symbs) {
        std::shared_ptr<instrument> iptr = add_instrument(a);
        if (iptr) {
            capFileReader.add_instrument(iptr);
            symbol_observer(a, callback);
        }
    }
}

void global_basket::symbol_observer(std::string symbol, std::function<void(std::string)> symbol_changed_callback) {
    observers[symbol].push_back(symbol_changed_callback);
}

std::function<void(instrument &, const std::string &)> global_basket::instrument_callback() {
    std::function<void(instrument &, const std::string &)> callback;
    callback = [this](instrument & i, std::string symbol){
        auto call_vector = observers[symbol];
        std::cout << "Notified change on : " << symbol;
        for (auto& a : call_vector) a(symbol);
    };
    return callback;
}




