//
// Created by b.karjoo on 3/21/2017.
//

#include "st_notifier.h"

void st_notifier::notify(std::shared_ptr<st_message> msg_ptr) {
    auto it = instruments.find(msg_ptr->getSymbol());
    if (it != instruments.end()) it->second->on_message(msg_ptr);
    market->notify(msg_ptr->getSymbol());
}

void st_notifier::add_instrument(std::shared_ptr<instrument> instr) {
    instruments.insert(std::make_pair(instr->getSymbol(),instr));
    market->add_instrument(instr);
}

void st_notifier::add_instrument(std::string symbol) {
    std::shared_ptr<instrument> sp = std::make_shared<instrument>(symbol);
    instruments.insert(std::make_pair(symbol, sp));
    market->add_instrument(sp);
}

st_notifier::st_notifier() {
    market = market_simulator::market();
}

