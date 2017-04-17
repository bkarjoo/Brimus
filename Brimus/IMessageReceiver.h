//
// Created by Behrooz Karjoo on 4/15/17.
//

#ifndef BRIMUS_IMESSAGEREADER_H
#define BRIMUS_IMESSAGEREADER_H

#include "st_message.h"

class IMessageReceiver
{
public:
    virtual void on_message(const st_message&) = 0;
    virtual bool has_instrument(const std::string&) = 0;
};

#endif //BRIMUS_IMESSAGEREADER_H
