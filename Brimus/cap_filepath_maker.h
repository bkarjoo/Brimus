//
// Created by Behrooz Karjoo on 4/15/17.
//

#ifndef BRIMUS_CAP_FILEPATH_MAKER_H
#define BRIMUS_CAP_FILEPATH_MAKER_H

#include "stdafx.h"
#include "strategy_launch_rules.h"

/*
 * give this class launch rules(s) of your strategy(s)
 * call construct paths
 * get a set of paths
 */
class cap_filepath_maker {
    std::vector<std::string> paths;
    void construct_paths();
    std::set<boost::gregorian::date> dates;
public:
    const std::vector<std::string>& get_paths();
    void add_launch_rules(const strategy_launch_rules&);
};


#endif //BRIMUS_CAP_FILEPATH_MAKER_H
