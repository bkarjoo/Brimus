//
// Created by b.karjoo on 3/20/2017.
//

#ifndef BRIMUS_READ_MODE_H
#define BRIMUS_READ_MODE_H

enum class capfile_read_mode {
    PACKET_HEADER,
    MSG_HEADER,
    FIELD,
    IGNORE_MSG,
    IGNORE_PACKET
};

#endif //BRIMUS_READ_MODE_H
