//
// Created by b.karjoo on 3/23/2017.
//

#include "bar_series.h"
#include <iostream>
#include <cmath>

using std::cout; using std::endl;

void bar_series::add_price(std::string timestamp, double price) {

    bar_time t(timestamp);
    bar_time start_time(t.getHours(),t.getMinutes());

    // TODO need mutex somewhere when this is changing
    if (current_bar == nullptr) {
        unsigned short int minute = start_time.getMinutes();
        // first bar starts on a proper start time, so take back minutes until you get there
        while (minute % bar_duration != 0 && minute > 0) minute--;
        bar_time nt(start_time.getHours(),minute);
        current_bar = std::make_shared<bar>(start_time);
        bars[nt] = current_bar;
        for (auto a : newBarObservers) a(symbol);
    } else if (current_bar->getStartTime().getMinutes() != start_time.getMinutes()) {
        // check if new bar needs to be created
        if (start_time.getMinutes() % bar_duration == 0) {
            // time for new bar

            current_bar = std::make_shared<bar> (start_time);
            bars[start_time] = current_bar;
            for (auto a : newBarObservers) a(symbol);
        }
    }
    current_bar->add_tick(timestamp, price);
}


std::string bar_series::to_string() const {
    std::string str;
    for (auto& a : bars) {
        str += a.first.to_string(); str += ' ';
        str += std::to_string(a.second->Open()); str += ' ';
        str += std::to_string(a.second->High()); str += ' ';
        str += std::to_string(a.second->Low()); str += ' ';
        str += std::to_string(a.second->Close()); str += '\n';
    }
    return str;
}



unsigned short bar_series::getBar_duration() const {
    return bar_duration;
}

void bar_series::setBar_duration(unsigned short bar_duration) {
    if (bar_duration != 1 && bar_duration != 2
        && bar_duration != 3 && bar_duration != 5
        && bar_duration != 6 && bar_duration != 10
        && bar_duration != 15 && bar_duration != 30) return;
    bar_series::bar_duration = bar_duration;
}

std::function<void(const stock&, stock_field)> bar_series::get_callback() {
    std::function<void(const stock&, stock_field )> callback =
            [this](const stock& stk, stock_field sf) {
                bar_time t(stk.getTimestamp());
                bar_time start_time(t.getHours(),t.getMinutes());

                if (!current_bar) {
                    unsigned short int minute = start_time.getMinutes();
                    // first bar starts on a proper start time, so take back minutes until you get there
                    while (minute % bar_duration != 0 && minute > 0) minute--;
                    bar_time nt(start_time.getHours(),minute);
                    current_bar = std::make_shared<bar>(start_time); 
                    bars[nt] = current_bar;
                    for (auto a : newBarObservers) a(symbol);
                } else {//if (current_bar->getStartTime().getMinutes() != start_time.getMinutes()) {
                    cout << current_bar->High() << endl;
                    // check if new bar needs to be created
                    if (start_time.getMinutes() % bar_duration == 0) {
                        // time for new bar
                        current_bar = std::make_shared<bar>(start_time); 
                        bars[start_time] = current_bar;
                        for (auto a : newBarObservers) a(symbol);
                    }
                }
                current_bar->add_tick(stk.getTimestamp(), stk.Last());
            };
    return callback;
}

const std::shared_ptr<bar> bar_series::PreviousBar(unsigned int i) const {
    int count = -1;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        count ++;
        if (count == i) return a->second;
    }
    return nullptr;
}

double bar_series::AverageClose(int numberOfBars) {
    if (numberOfBars < 1) return 0;
    int count = 0;
    double sum =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) sum += a->second->Close(); else break;
        count ++;
    }
    return sum / numberOfBars;
}

/*
 * bars back is the starting point, so 1 would be start from one bar back
 */
double bar_series::AverageClose(int numberOfBars, int barsBack) {
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double sum = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars)
                sum += a->second->Close();
            else
                break;
        }
        count ++;
    }
    return sum / numberOfBars;
}

double bar_series::AverageHigh(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double sum =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) sum += a->second->High(); else break;
        count ++;
    }
    return sum / numberOfBars;

}
double bar_series::AverageHigh(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double sum = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars)
                sum += a->second->High();
            else
                break;
        }
        count ++;
    }
    return sum / numberOfBars;
}
double bar_series::AverageLow(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double sum =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) sum += a->second->Low(); else break;
        count ++;
    }
    return sum / numberOfBars;
}
double bar_series::AverageLow(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double sum = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars)
                sum += a->second->Low();
            else
                break;
        }
        count ++;
    }
    return sum / numberOfBars;
}

const std::string &bar_series::getSymbol() const {
    return symbol;
}

void bar_series::setSymbol(const std::string &symbol) {
    bar_series::symbol = symbol;
}

void bar_series::AddNewBarObserver(std::function<void(std::string)> observer) {
    newBarObservers.push_back(observer);
}

double bar_series::MaxClose(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double max =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (max < a->second->Close()) max = a->second->Close();
        }
        else
            break;
        count ++;
    }
    return max;
}
double bar_series::MaxClose(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double max = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (max < a->second->Close()) max = a->second->Close();
            }
            else
                break;
        }
        count ++;
    }
    return max;
}
double bar_series::MaxHigh(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double max =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (max < a->second->High()) max = a->second->High();
        }
        else
            break;
        count ++;
    }
    return max;
}
double bar_series::MaxHigh(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double max = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (max < a->second->High()) max = a->second->High();
            }
            else
                break;
        }
        count ++;
    }
    return max;
}
double bar_series::MaxLow(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double max =0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (max < a->second->Low()) max = a->second->Low();
        }
        else
            break;
        count ++;
    }
    return max;
}
double bar_series::MaxLow(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double max = 0;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (max < a->second->Low()) max = a->second->Low();
            }
            else
                break;
        }
        count ++;
    }
    return max;
}

double bar_series::MinClose(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double min =100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (min > a->second->Close()) min = a->second->Close();
        }
        else
            break;
        count ++;
    }
    return min;
}
double bar_series::MinClose(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double min = 100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (min > a->second->Close()) min = a->second->Close();
            }
            else
                break;
        }
        count ++;
    }
    return min;
}
double bar_series::MinHigh(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double min =100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (min > a->second->High()) min = a->second->High();
        }
        else
            break;
        count ++;
    }
    return min;
}
double bar_series::MinHigh(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double min = 100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (min > a->second->High()) min = a->second->High();
            }
            else
                break;
        }
        count ++;
    }
    return min;
}
double bar_series::MinLow(int numberOfBars)
{
    if (numberOfBars < 1) return 0;
    int count = 0;
    double min =100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count < numberOfBars) {
            if (min > a->second->Low()) min = a->second->Low();
        }
        else
            break;
        count ++;
    }
    return min;
}
double bar_series::MinLow(int numberOfBars, int barsBack)
{
    if (numberOfBars < 1) return 0;
    int count = 0 - barsBack;
    double min = 100000;
    for (auto a = bars.rbegin(); a != bars.rend(); a++) {
        if (count >= 0) {
            if (count < numberOfBars) {
                if (min > a->second->Low()) min = a->second->Low();
            }
            else
                break;
        }
        count ++;
    }
    return min;
}