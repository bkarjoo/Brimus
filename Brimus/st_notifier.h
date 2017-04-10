//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_ST_NOTIFIER_H
#define BRIMUS_ST_NOTIFIER_H


#include "stdafx.h"
#include "instrument.h"
#include "market_simulator.h"
#include "ISTNotifier.h"

class st_notifier : public ISTNotifier {
    std::map<std::string, std::shared_ptr<instrument> > instruments;
public:
    st_notifier();
    void notify(std::shared_ptr<st_message>);
    void add_instrument(std::shared_ptr<instrument>);
    void add_instrument(std::string);
};


#endif //BRIMUS_ST_NOTIFIER_H
