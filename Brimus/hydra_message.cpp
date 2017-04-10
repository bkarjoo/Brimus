//
// Created by b.karjoo on 4/7/2017.
//


#include "hydra_message.h"
using namespace std;

std::string hydra_message::make_login_msg(int serial, std::string login, std::string password) {
    stringstream ss,ss2;
    string s1,s2,s3;
    ss << '#' << ':' << "00000" << ':' << 'I' << ':';
    s1 = ss.str();
    ss2 << ':' << serial << ':' << login << ':' << password << ':' << '*';
    s3 = ss2.str();
    int length = s1.length() + s3.length() + 3;
    s2 = (length < 100 ? ("0" + std::to_string(length)) : std::to_string(length));
    return s1 + s2 + s3;
}

std::string hydra_message::make_trader_login_msg(int serial, std::string login, std::string password) {
    stringstream ss,ss2;
    string s1,s2,s3;
    ss << '#' << ':' << "00000" << ':' << 'I' << ':';
    s1 = ss.str();
    ss2 << ':' << serial << ':' << login << ':' << password << ':' << 'T' << ':' << '*';
    s3 = ss2.str();
    int length = s1.length() + s3.length() + 3;
    s2 = (length < 100 ? ("0" + std::to_string(length)) : std::to_string(length));
    return s1 + s2 + s3;
}
