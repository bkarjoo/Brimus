//
// Created by b.karjoo on 4/17/2017.
//

#ifndef BRIMUS_MESSAGE_ROUTER_H
#define BRIMUS_MESSAGE_ROUTER_H

#include "stdafx.h"
#include "IMessageReceiver.h"
#include "stock_collection.h"

class message_router : public IMessageReceiver {

public:
    void on_packet_header(const std::string &string) override;

    message_router();

    void on_message(const cap_message &message) override;

    bool has_instrument(const std::string &string) override;

    boost::posix_time::ptime convert_time(std::string);

    std::string mock_time_stamp(const std::string &basic_string);
};


#endif //BRIMUS_MESSAGE_ROUTER_H
