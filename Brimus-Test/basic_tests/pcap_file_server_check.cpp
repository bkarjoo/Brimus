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
    std::set<boost::gregorian::date> items;
    for (auto a : date_set) items.insert(*a);
    EXPECT_EQ(3, date_set.size());
    EXPECT_EQ(2014,items.begin()->year());
    EXPECT_EQ(2,items.begin()->day());
    EXPECT_EQ(1,items.begin()->month().as_number());
}

TEST(pcap_file_server_tests, test2)
{
    std::shared_ptr<launch_rules> lr = std::make_shared<launch_rules>();
    lr->setStartDate(2016,1,1);
    lr->setEndDate(2016,1,7);
    lr->set_date_range();
    pcap_file_server& pfs = pcap_file_server::get_instance();
    pfs.clear_date_set();
    pfs.request_data(lr);
    auto& pathvec = pfs.get_paths();
    EXPECT_TRUE(pathvec.size() > 0);
    EXPECT_EQ("E:\\2016\\2016-01-04 Daily.CAP", pathvec[0]);

}
