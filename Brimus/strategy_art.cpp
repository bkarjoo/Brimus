//
// Created by b.karjoo on 3/24/2017.
//

#include "strategy_art.h"
#include "instrument.h"

using std::cout; using std::endl;

void strategy_art::notify(std::string s) {
    strategy::notify(s);



//    if (positions[symbol] <= 0) {
//        if (instruments[symbol]->getAsk_price() != 0 && instruments[symbol]->getLast_price() != 0)
//            broker->send_order(100, symbol, instruments[symbol]->getAsk_price() + .01, this);
//    }
//    else {
//        if (instruments[symbol]->getBid_price() != 0 && instruments[symbol]->getLast_price() != 0)
//            broker->send_order(-100, symbol, instruments[symbol]->getBid_price() - .01, this);
//    }
//    if (instruments[s]->getLast_price() != 0)
//        cout << instruments[s]->getBars().to_string() << endl;
}

//void strategy_art::add_instrument(std::shared_ptr<instrument> i) {
//    std::string symbol = i->getSymbol();
//    instruments[symbol] = i;
//    //i->set_strategy(this);
//    // initialize a bar series
//    std::shared_ptr<bar_series> bs = std::make_shared<bar_series>(symbol);
//    bs->setBar_duration(5);
//    bs->AddNewBarObserver(get_on_new_bar_callback());
//    i->setLast_observer(bs->instrument_callback());
//    FiveMinute[symbol] = bs;
//}

bool strategy_art::entryConditions(std::string s) {
    // check for buy signal
    try {
        auto bars_ptr = FiveMinute[s]; if (bars_ptr == nullptr) return false;
        auto prev_bar = bars_ptr->PreviousBar(1); if (prev_bar == nullptr) return false;


        double prev5mClose = prev_bar->get_close();
        double avgLow3Bars = bars_ptr->AverageLow(3, 1);
        double prev5mHigh = prev_bar->get_high();
        double avgHigh3Bars = bars_ptr->AverageHigh(3, 1);
        double minClose5Bars = bars_ptr->MinClose(5, 1);

        //double fiveBarMinClose = FiveMinute[s]->AverageClose()
        if (prev5mClose <= avgLow3Bars
            && prev5mHigh < avgHigh3Bars
            && prev5mClose < minClose5Bars)
            return true;
        // check for sell short signal


        return false;
    } catch (std::exception& e) {
        cout << e.what() << endl;
    }
}

void strategy_art::placeEntryOrders(std::string symbol) {

}

bool strategy_art::exitConditions(std::string symbol) {
    return false;
}

void strategy_art::placeExitOrders(std::string symbol) {

}



std::function<void(std::string)> strategy_art::get_on_new_bar_callback() {
    std::function<void(std::string)> callback =
            [this](std::string symbol) {
                cout << "Received New Bar Callback for : " << symbol << endl;

                if (entryConditions(symbol))
                    placeEntryOrders(symbol);
                else if (exitConditions(symbol))
                    placeExitOrders(symbol);

                cout << FiveMinute[symbol]->to_string() << endl;
                if (FiveMinute[symbol]->CurrentBar() != nullptr)
                    cout << "Current High: " << FiveMinute[symbol]->CurrentBar()->get_high() << endl;
                if (FiveMinute[symbol]->PreviousBar(1) != nullptr)
                    cout << "Previous High: " <<  FiveMinute[symbol]->PreviousBar(1)->get_high() << endl;
                if (FiveMinute[symbol]->PreviousBar(2) != nullptr)
                    cout << "Previous 2 High: " << FiveMinute[symbol]->PreviousBar(2)->get_high() << endl;

            };
    return callback;
}
