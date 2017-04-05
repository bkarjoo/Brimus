//
// Created by b.karjoo on 4/5/2017.
//

#ifndef BRIMUS_ISTRATEGYRULES_H
#define BRIMUS_ISTRATEGYRULES_H

#include <memory>
#include <string>
#include "strategy_oms.h"

class IStrategyRules {
public:
    virtual void set_oms(std::shared_ptr<strategy_oms>) = 0;
    virtual bool update_on() = 0;
    virtual void update(std::string) = 0;

    virtual bool long_entry_rules(std::string) = 0;
    virtual bool short_entry_rules(std::string) = 0;
    virtual bool long_target_rules(std::string) = 0;
    virtual bool short_target_rules(std::string) = 0;
    virtual bool long_stoploss_rules(std::string) = 0;
    virtual bool short_stoploss_rules(std::string) = 0;

    virtual void place_long_entry(std::string) = 0;
    virtual void place_short_entry(std::string) = 0;
    virtual void place_long_target(std::string) = 0;
    virtual void place_short_target(std::string) = 0;
    virtual void place_long_stoploss(std::string) = 0;
    virtual void place_short_stoploss(std::string) = 0;
};


#endif //BRIMUS_ISTRATEGYRULES_H
