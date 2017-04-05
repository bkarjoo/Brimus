//
// Created by b.karjoo on 4/4/2017.
//

#ifndef BRIMUS_ISTNOTIFIER_H
#define BRIMUS_ISTNOTIFIER_H

#include <memory>
#include "st_message.h"
#include "instrument.h"

class ISTNotifier {
public:
    virtual void notify(std::shared_ptr<st_message>) = 0;
    virtual void add_instrument(std::shared_ptr<instrument>) = 0;
    virtual void add_instrument(std::string) = 0;
};


#endif //BRIMUS_ISTNOTIFIER_H
