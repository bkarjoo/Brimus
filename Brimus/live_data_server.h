//
// Created by b.karjoo on 3/31/2017.
//

#ifndef BRIMUS_LIVE_DATA_SERVER_H
#define BRIMUS_LIVE_DATA_SERVER_H


#include "IDataServer.h"

class live_data_server : public IDataServer {
    live_data_server() {}
    ~live_data_server() {}
public:
    live_data_server(live_data_server const&) = delete;
    void operator=(live_data_server const&) = delete;
    static live_data_server& get_instance() {
        static live_data_server lds;
        return lds;
    }
    void request_data(std::shared_ptr<launch_rules> ptr) override;

};


#endif //BRIMUS_LIVE_DATA_SERVER_H
