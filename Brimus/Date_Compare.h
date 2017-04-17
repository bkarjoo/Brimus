//
// Created by b.karjoo on 4/3/2017.
//

#ifndef BRIMUS_DATE_COMPARE_H
#define BRIMUS_DATE_COMPARE_H
#include "stdafx.h"


typedef boost::gregorian::date bdate;
typedef std::shared_ptr<bdate> DatePtr;

/*
 * a class to compare facilitate comparison of boost date objects with operators
 * used in file_server, launch_rules, and holidays
 * as second parameter of a set, used to keep the dates in order
 */
struct Date_Compare {
    using is_transparent = void;

    bool operator() (const DatePtr& a, const DatePtr& b) const
    {
        return *a < *b;
    }

    bool operator() (const DatePtr& a, bdate b) const
    {
        return *a < b;
    }

    bool operator() (bdate a, const DatePtr& b) const
    {
        return a < *b;
    }
};


#endif //BRIMUS_DATE_COMPARE_H
