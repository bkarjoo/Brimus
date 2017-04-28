//
// Created by b.karjoo on 4/26/2017.
//

#ifndef BRIMUS_MINI_CAP_READER_H
#define BRIMUS_MINI_CAP_READER_H

#include <string>
#include <vector>
/*
 * difference betwee this cap reader and previous one is
 * in this one there's no packet delimiter, and there are no precisions
 */
class mini_cap_reader {
    void process_char(const char&);
    char prev1;
    char prev2;
public:
    void read(const std::vector<std::string> &);
};


#endif //BRIMUS_MINI_CAP_READER_H
