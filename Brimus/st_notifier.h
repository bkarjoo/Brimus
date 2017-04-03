//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_ST_NOTIFIER_H
#define BRIMUS_ST_NOTIFIER_H


#include <map>
#include <memory>
#include "instrument.h"
#include "market_simulator.h"

class st_notifier {
    std::shared_ptr<market_simulator> market = nullptr;
    std::map<std::string, std::shared_ptr<instrument> > instruments;
public:
    st_notifier();
    void notify(std::shared_ptr<st_message>);
    void add_instrument(std::shared_ptr<instrument>);
    void add_instrument(std::string);
};


#endif //BRIMUS_ST_NOTIFIER_H
