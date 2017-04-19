//
// Created by b.karjoo on 4/19/2017.
//

#ifndef BRIMUS_S_SPYART_FACTORY_H
#define BRIMUS_S_SPYART_FACTORY_H


#include "strategy.h"

class S_SpyArt_Factory {
public:

    static std::unique_ptr<strategy> get_strat();
};


#endif //BRIMUS_S_SPYART_FACTORY_H
