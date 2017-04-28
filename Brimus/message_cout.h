//
// Created by b.karjoo on 4/28/2017.
//

#ifndef BRIMUS_MESSAGE_COUT_H
#define BRIMUS_MESSAGE_COUT_H

#include "stdafx.h"
#include "IMessageReceiver.h"

class message_cout : public IMessageReceiver {
public:
    void on_packet_header(const std::string &string) override;

    void on_message(const cap_message &message) override;

    bool has_instrument(const std::string &string) override;
};


#endif //BRIMUS_MESSAGE_COUT_H
