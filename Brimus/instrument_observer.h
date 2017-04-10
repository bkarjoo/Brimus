//
// Created by b.karjoo on 3/24/2017.
//

#ifndef BRIMUS_INSTRUMENT_OBSERVER_H
#define BRIMUS_INSTRUMENT_OBSERVER_H

#include "stdafx.h"
class instrument_observer {
public:
    virtual void notify(std::string) = 0;
};


#endif //BRIMUS_INSTRUMENT_OBSERVER_H
