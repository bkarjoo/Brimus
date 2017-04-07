//
// Created by b.karjoo on 4/7/2017.
//

#ifndef BRIMUS_HYDRA_MESSAGE_H
#define BRIMUS_HYDRA_MESSAGE_H
#include <string>

class hydra_message {
    hydra_message() {}
public:
    static std::string make_login_msg(int, std::string, std::string);
    static std::string make_trader_login_msg(int, std::string, std::string);
};


#endif //BRIMUS_HYDRA_MESSAGE_H
