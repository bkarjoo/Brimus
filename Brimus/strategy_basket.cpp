//
// Created by b.karjoo on 3/30/2017.
//


#include "strategy_basket.h"



void strategy_basket::add_strategy(const std::shared_ptr<strategy> strat) {
    strategies.push_back(strat);
    // wire up data
    if (strat->getRunMode() == run_mode::BACKTEST)
        pcap_file_server::get_instance().request_data(strat->getLaunchRules());
    else if (strat->getRunMode() == run_mode::LIVE)
        live_data_server::get_instance().request_data(strat->getLaunchRules());
    // subscribe to symbols

    global_basket::get_instance().add_basket(
            strat->getSymbolBakset(), strat->get_symbol_update_callback()
    );
}

void strategy_basket::run_backtests() {
    pcap_file& pcf = pcap_file::get_instance();
    pcf.run(pcap_file_server::get_instance().get_paths());
}
