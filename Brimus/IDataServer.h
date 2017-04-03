//
// Created by b.karjoo on 3/31/2017.
//

#ifndef BRIMUS_IDATASERVER_H
#define BRIMUS_IDATASERVER_H

#include <memory>
#include <set>
#include <time.h>
#include "launch_rules.h"

class IDataServer {
public:
    virtual void request_data(std::shared_ptr<launch_rules>) = 0;
};


#endif //BRIMUS_IDATASERVER_H
