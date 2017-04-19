//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_ST_FIELD_H
#define BRIMUS_ST_FIELD_H
#include "stdafx.h"

struct cap_msg_field {
    char field_exchange;
    char field_code;
    std::string field_code_value;
    std::string field_value;
};


#endif //BRIMUS_ST_FIELD_H
