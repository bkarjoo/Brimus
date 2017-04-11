//
// Created by b.karjoo on 4/11/2017.
//

#ifndef BRIMUS_MS_EXECUTION_COLLECTION_H
#define BRIMUS_MS_EXECUTION_COLLECTION_H

#include "stdafx.h"
#include "ms_execution.h"

class ms_execution_collection {
    typedef std::unique_ptr<ms_execution> exec_ptr;
    typedef std::vector<exec_ptr> exec_vector;
    exec_vector executions;
public:
    void add_execution(std::unique_ptr<ms_execution>);
    exec_vector::iterator begin() { return executions.begin(); }
    exec_vector::iterator end() { return executions.end(); }
};


#endif //BRIMUS_MS_EXECUTION_COLLECTION_H
