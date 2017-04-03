#include <memory>
#include <iostream>
#include <chrono>
#include "pcap_file.h"
#include "strategy.h"
#include <boost/date_time.hpp>
#include <global_basket.h>
#include <pcap_file_server.h>
#include <symbol_basket.h>
#include <launch_rules.h>


// takes one file and breaks it down into symbol files
void cap_file_breakdown(std::string full_path) {
    // pcap file has an all notification option
    // pcap file has too many responsibilities
    // distributing notifications should be the task of another task
}


/*
 * command line prompt for controlling program features
 *
 */
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();

    auto& pcf = pcap_file::get_instance();

    // create a vector of file paths to feed to run method of pcf
    pcap_file_server& pfs = pcap_file_server::get_instance();
    //pcf.run(pfs.get_paths());
    // set up strategies
    std::shared_ptr<symbol_basket> sb = std::make_shared<symbol_basket>();
    sb->add_symbol("AAPL");
    std::shared_ptr<launch_rules> lr = std::make_shared<launch_rules>();
    lr->add_date(2017,1,3);
    std::shared_ptr<strategy> s = std::make_shared<strategy>(lr,sb);
    std::shared_ptr<strategy_basket> stb = std::make_shared<strategy_basket>();
    stb->add_strategy(s);
    stb->run_backtests();

//    Person& p = Person::get_instance();
//    {
//        p.PropertyChanged.connect([](Person &, const std::string &property_name) {
//            std::cout << property_name << " Has been changed.";
//        });
//    }
//    p.setAge(20);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    long ms = (long)(1000*diff.count());
    std::cout << "Completed in: " << ms << " miliseconds." << std::endl;
    return 0;
}