//
// Created by b.karjoo on 4/11/2017.
//

#include "ms_execution_collection.h"

void ms_execution_collection::add_execution(std::unique_ptr<ms_execution> exec) {
    executions.push_back(move(exec));
}
