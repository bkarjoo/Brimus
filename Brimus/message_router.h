//
// Created by b.karjoo on 4/17/2017.
//

#ifndef BRIMUS_MESSAGE_ROUTER_H
#define BRIMUS_MESSAGE_ROUTER_H

#include "stdafx.h"
#include "IMessageReceiver.h"
#include "stock_collection.h"

class message_router : public IMessageReceiver {
    boost::optional<stock_collection&> sc;
public:
    message_router();

    void on_message(const cap_message &message) override;

    bool has_instrument(const std::string &string) override;
};


#endif //BRIMUS_MESSAGE_ROUTER_H
