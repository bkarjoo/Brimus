//
// Created by b.karjoo on 3/30/2017.
//

#ifndef BRIMUS_LAUNCH_RULES_H
#define BRIMUS_LAUNCH_RULES_H

#include <memory>
#include <set>
#include <string>
#include <vector>
#include <time.h>

class launch_rules {
    std::vector<std::shared_ptr<tm>> dates;
public:
    const std::vector<std::shared_ptr<tm>> &getDates() const;
    ~launch_rules() {}
    void add_date(int year, int month, int day);
    std::string to_string() const;
};


#endif //BRIMUS_LAUNCH_RULES_H
