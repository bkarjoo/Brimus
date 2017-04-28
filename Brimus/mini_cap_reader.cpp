//
// Created by b.karjoo on 4/26/2017.
//
#include "stdafx.h"
#include "mini_cap_reader.h"
using namespace std;

void mini_cap_reader::read(const vector<string>& paths) {
    for (auto path : paths) {
        ifstream fs(path);
        char c;

        while (c = fs.get()) {
            if (c == ':') {

            }
            prev2 = prev1;
            prev1 = c;
        }
    }
}

void mini_cap_reader::process_char(const char &c) {
    cout << c;
}
