//
// Created by b.karjoo on 4/5/2017.
//
#include "stdafx.h"
#include "gtest/gtest.h"
#include "pcap_file.h"
#include "st_notifier.h"

using namespace std;
typedef shared_ptr<st_notifier> notifier;

/*
 * pcap_file takes a notifier,
 */
TEST(pcap_file_tests, test1) {
    pcap_file& pf = pcap_file::get_instance();
    notifier n = std::make_shared<st_notifier>();
    pf.set_notifier(n);
    pf.setStart_time_seconds(((9*60)+30)*60);
    pf.setEnd_time_seconds(((16*60)+15)*60);
    pf.add_instrument("SPY");
    vector<string> paths { "C:\\Users\\b.karjoo\\Documents\\Brimus\\cmake-build-debug\\SPY.CAP"};
    pf.run(paths);
    EXPECT_EQ(1,1);
}
