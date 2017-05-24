//
// Created by b.karjoo on 4/28/2017.
//

#include "message_cout.h"
using namespace std;
void message_cout::on_packet_header(const std::string &string) {
    cout << endl << string << endl << endl;
//    char a ;
//    cin >> a;
}

void message_cout::on_message(const cap_message &message) {
    cout << message.to_string() << endl;
//    char a;
//    cin >> a;
}

bool message_cout::has_instrument(const std::string &symbol) {
    return symbol == "SPY";
}
