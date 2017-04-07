
#include <boost/tokenizer.hpp>
#include <chrono>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <st_notifier.h>
#include <tick_file_maker.h>
#include <S_SpyArt.h>
#include "global_basket.h"
#include "pcap_file.h"
#include "strategy.h"

using boost::tokenizer;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;

void print_menu();
void command_interpretter(vector<string> tokens);
void run(vector<string>);
void extract(vector<string>);
struct param;

typedef vector<std::shared_ptr<param>> param_vec;

struct param {
    string parameter = "";
    string value = "";
    param(boost::tokenizer<boost::char_separator<char>> tokens) {
        for (auto& a : tokens)
        {
            if (parameter != "" & value == "")
                value = a;
            else
                parameter = a;

        }
    }
};



void run(param_vec parameters)
{
    auto &pcf  = pcap_file::get_instance();
    auto notifier = std::make_shared<st_notifier>();pcf.set_notifier(notifier);
    auto & gb = global_basket::get_instance();
    auto basket = std::make_shared<symbol_basket>();basket->add_symbol("SPY");
    auto launch = std::make_shared<launch_rules>();

    strategy* sptr = new strategy (launch,basket);
    gb.add_basket(basket,sptr->get_symbol_update_callback());

    auto rules = std::make_shared<S_SpyArt>();
    sptr->setRules(rules);


    std::vector<std::string> paths {"C:\\Users\\b.karjoo\\Documents\\Brimus\\cmake-build-debug\\SPY.CAP"};
    pcf.run(paths);


//    std::cout << "In run" << std::endl;
//    auto& pcf = pcap_file::get_instance();
//    std::shared_ptr<st_notifier> notifier = std::make_shared<st_notifier>();
//    pcf.set_notifier(notifier);
//    // create a vector of file paths to feed to run method of pcf
//    pcap_file_server& pfs = pcap_file_server::get_instance();
//    //pcf.run(pfs.get_paths());
//    // set up strategies
//    std::shared_ptr<symbol_basket> sb = std::make_shared<symbol_basket>();
//    sb->add_symbol("SPY");
//    std::shared_ptr<launch_rules> lr = std::make_shared<launch_rules>();
//    lr->add_date(2017,1,3);
//    std::shared_ptr<strategy> s = std::make_shared<strategy>(lr,sb);
//    std::shared_ptr<IStrategyRules> r (new S_DoNothing);
//    s->setRules(r);
//    std::shared_ptr<strategy_basket> stb = std::make_shared<strategy_basket>();
//    stb->add_strategy(s);
//    std::cout << "Start Running" << std::endl;
//    stb->run_backtests();
    std::cout << "Done Running" << std::endl;
}

void extract(param_vec parameters)
{
    string output_path = "output.CAP";
    string symbol = "SPY";
    string default_path = "C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40000.CAP";
    vector<string> paths;
    for (auto & a : parameters) {
        if (a->parameter == "output") output_path = a->value;
        else if (a->parameter == "symbol") symbol = a->value;
        else if (a->parameter == "input") paths.push_back(a->value);
    }
    if (paths.size() == 0) paths.push_back(default_path);
    pcap_file& pf = pcap_file::get_instance();
    pf.setStart_time_seconds(((9 * 60) + 30) * 60);
    pf.setEnd_time_seconds(((16 * 60) + 15) * 60);
    std::shared_ptr<tick_file_maker> tfmptr =
        std::make_shared<tick_file_maker>(output_path);
    pf.set_notifier(tfmptr);
    pf.add_instrument(symbol);
    pf.run(paths);
    tfmptr->close_os();
    cout << endl;
    cout << "Exctract completed." << endl;
}

void print_menu() {
    cout << endl;
    cout << "----    command list    ----" << endl; cout << endl;
    cout << "extract - extracts tick data for a symbol" << endl;
    cout << "    output=file_path";
    cout << "    symbol=SPY";
    cout << "menu - prints this menu" << endl;
    cout << "quit - quits the program" << endl;
    cout << "run - runs a strategy backtest (inprog>" << endl;
    cout << endl;
}

void command_interpretter(std::string choice, param_vec tokens)
{
    //if (tokens.size() == 0) return;
    if (choice == "menu") print_menu();
    else if (choice == "run") run(tokens);
    else if (choice == "extract") extract(tokens);
}

/*
 * command line prompt for controlling program features
 *
 */
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    // timer begin

    string s;
    vector<string> v;
    cout << "Welcome" << endl;
    print_menu();
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{" "};
    boost::char_separator<char> eq{"="};
    while (true)
    {
        getline(cin, s);
        if (s == "quit") break;

        tokenizer tok{s, sep};
        string command = "";
        param_vec tokens;
        for (auto a : tok) {
            if (command == "")
                command = a;
            else {
                tokenizer eq_tok{a, eq};
                std::shared_ptr<param> p = std::make_shared<param>(eq_tok);
                tokens.push_back(p);
            }
        }
        command_interpretter(command, tokens);
    }

    // timer end
    auto t2 = std::chrono::high_resolution_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    long ms = (long)(1000*diff.count());
    std::cout << "Completed in: " << ms << " miliseconds." << std::endl;
    return 0;
}