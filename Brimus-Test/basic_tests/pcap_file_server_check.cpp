//
// Created by b.karjoo on 3/31/2017.
//

#include "gtest/gtest.h"
#include "pcap_file_server.h"
#include "launch_rules.h"
#include <sys/param.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <ctime>

TEST(pcap_file_server_tests, test1)
{
    std::shared_ptr<launch_rules> lr = std::make_shared<launch_rules>();
    lr->add_date(2015,1,3);
    lr->add_date(2014,1,2);
    lr->add_date(2015,1,1);
    pcap_file_server& pfs = pcap_file_server::get_instance();
    pfs.request_data(lr);
    auto& date_set = pfs.getDates();
    std::vector<tm> items;
    for (auto a : date_set) items.push_back(*a);
    EXPECT_EQ(3, date_set.size());
    EXPECT_EQ(2015,items[0].tm_year);
    EXPECT_EQ(1,items[0].tm_mday);
}
