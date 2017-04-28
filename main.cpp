#include <S_SpyArt_Factory.h>
#include "message_router.h"
#include "cap_file_reader.h"
#include "stdafx.h"
#include "tick_file_maker.h"
#include "S_SpyArt.h"
#include "stock_collection.h"
#include "strategy.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <message_cout.h>

using boost::tokenizer;
using namespace std;
using namespace boost::filesystem;

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
//    auto &pcf  = pcap_file::get_instance();
//    auto notifier = std::make_shared<st_notifier>();pcf.set_notifier(notifier);
    stock_collection& sc = stock_collection::get_instance();
    //cout << sc.size() << endl;
    auto strat = S_SpyArt_Factory::get_strat();
    auto & cfr = cap_file_reader::get_instance();
    std::vector<std::string> paths {"F:\\2017-01-03 Daily.CAP"};
    cfr.setImr(make_unique<message_router>());
    //cout << sc.size() << endl;
    cfr.setStart_time_seconds(((9 * 60) + 30) * 60);
    cfr.setEnd_time_seconds(((16 * 60) + 15) * 60);
    cfr.run(paths);

   // cout << sc.size() << endl;

    std::cout << "Done Running" << std::endl;
    //cout << sc.size() << endl;
}

void extract(param_vec parameters)
{
    path myPath("E:\\2017\\");
    directory_iterator it(myPath), end;
    vector<string> paths;
    BOOST_FOREACH(path const&p, make_pair(it, end))
    {

        if (is_regular_file(p) && file_size(p) > 1000000000) {
            path can = canonical(p);
            string output_path = p.filename().string();
            string symbol = "SPY";
            string default_path = can.string();
            vector<string> paths;
            for (auto & a : parameters) {
                if (a->parameter == "output") output_path = a->value;
                else if (a->parameter == "symbol") symbol = a->value;
                else if (a->parameter == "input") paths.push_back(a->value);
            }
            paths.clear();
            if (paths.size() == 0) paths.push_back(default_path);
            auto& pf = cap_file_reader::get_instance();
            pf.setStart_time_seconds(((4 * 60) + 00) * 60);
            pf.setEnd_time_seconds(((20 * 60) + 00) * 60);
            auto tfmptr = std::make_unique<tick_file_maker>(output_path);
            auto& tfmref = *tfmptr;
            tfmptr->add_instrument(symbol);
            pf.setImr(move(tfmptr));
            pf.run(paths);
            tfmref.flush_stream();
            tfmref.close_os();
        }
    }

//    string output_path = "40000b.CAP";
//    //string output_path = "20170131noabs.CAP";
//    string symbol = "SPY";
//    string default_path = "C:\\Users\\b.karjoo\\Documents\\CMDCPP\\CapFileMaker\\output\\40000.CAP";
//    //string default_path = "E:\\2017\\2017-01-31 Daily.CAP";
//    vector<string> paths;
//    for (auto & a : parameters) {
//        if (a->parameter == "output") output_path = a->value;
//        else if (a->parameter == "symbol") symbol = a->value;
//        else if (a->parameter == "input") paths.push_back(a->value);
//    }
//    if (paths.size() == 0) paths.push_back(default_path);
//    auto& pf = cap_file_reader::get_instance();
//    pf.setStart_time_seconds(((4 * 60) + 00) * 60);
//    pf.setEnd_time_seconds(((20 * 60) + 00) * 60);
//    auto tfmptr = std::make_unique<tick_file_maker>(output_path);
//    auto& tfmref = *tfmptr;
//    tfmptr->add_instrument(symbol);
//    pf.setImr(move(tfmptr));
//    pf.run(paths);
//    cout << endl;
//    tfmref.flush_stream();
//    tfmref.close_os();
    cout << "Exctract completed." << endl;
}

void output(param_vec parameters) {
    cap_file_reader& cfr = cap_file_reader::get_instance();
    cfr.setImr(make_unique<message_cout>());
    std::vector<std::string> paths {"F:\\2017-01-03 Daily.CAP"};
    cfr.run(paths);
}

void print_menu() {
    cout << endl;
    cout << "----    command list    ----" << endl; cout << endl;
    cout << "extract - extracts tick data for a symbol" << endl;
    cout << "    output=file_path";
    cout << "    symbol=SPY" << endl;
    cout << "menu - prints this menu" << endl;
    cout << "quit - quits the program" << endl;
    cout << "run - runs a strategy backtest (inprog>" << endl;
    cout << "output - prints messages to screen" << endl;
    cout << endl;
}

void command_interpretter(std::string choice, param_vec tokens)
{
    //if (tokens.size() == 0) return;
    if (choice == "menu") print_menu();
    else if (choice == "run") run(tokens);
    else if (choice == "extract") extract(tokens);
    else if (choice == "output") output(tokens);
}

/*
 * command line prompt for controlling program features
 *
 */
int main() {

    auto t1 = std::chrono::high_resolution_clock::now();
    // timer begin
    boost::program_options::options_description desc("Program options");

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