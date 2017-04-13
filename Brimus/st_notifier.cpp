//
// Created by b.karjoo on 3/21/2017.
//

#include "st_notifier.h"
#include "global_basket.h"

void st_notifier::notify(std::shared_ptr<st_message> msg_ptr) {
    auto it = instruments.find(msg_ptr->getSymbol());
    if (it != instruments.end()) it->second->on_message(msg_ptr);
    market_simulator::get_instance().notify(msg_ptr->getSymbol());
}

void st_notifier::add_instrument(std::shared_ptr<instrument> instr) {
    global_basket& gb = global_basket::get_instance();
    auto i = gb.get_instrument_ptr(instr->getSymbol());
    if (i)
        instr = i;
    else {
        instr = gb.add_instrument(instr->getSymbol());
    }
    instruments[instr->getSymbol()] = instr;
}

void st_notifier::add_instrument(std::string symbol) {
    global_basket& gb = global_basket::get_instance();
    auto i = gb.get_instrument_ptr(symbol);
    if (!i) gb.add_instrument(symbol);
}

st_notifier::st_notifier() {

}

