//
// Created by b.karjoo on 3/21/2017.
//

#ifndef BRIMUS_INSTRUMENT_H
#define BRIMUS_INSTRUMENT_H

#include "stdafx.h"
#include "st_message.h"
#include "bar_series.h"
#include "INotifyPropertyChanged.h"


class instrument : public INotifyPropertyChanged<instrument> {
    // TODO : what class extends instrument? message printer
    // TODO : remove message printer as it has no is-a relation ship to instrument
protected:

    std::string symbol = "";
//    instrument_observer* my_strategy = nullptr;
    double last_price = 0.0;
    double ask_price = 0.0;
    double bid_price = 0.0;
    unsigned int bid_size = 0;
    unsigned int ask_size = 0;
    double open_price = 0.0;
    double close_price = 0.0;
    unsigned short int precision = 0;
    void register_field(st_field *pField);
    void set_precision(st_field *f);
    unsigned int set_volume(const std::string&);
    double set_price(const std::string&);
    std::string last_time_stamp = "";
    std::vector<std::function<void(std::string, double)> > last_observers;
    std::vector<std::function<void(std::string)>> update_observer;
public:
    instrument(std::string symb);
    instrument(std::string symb, std::function<void(std::string)> callback);
    static int instance_count;
    void setLast_observer(const std::function<void(std::string, double)> &last_observer);

    void setUpdate_observer(const std::vector<std::function<void(std::string)>> &update_observer);

    double getLast_price() const {  return last_price; }
    double getAsk_price() const { return ask_price; }

    const std::string &getLast_time_stamp() const;

    double getBid_price() const { return bid_price; }
    unsigned int getBid_size() const { return bid_size; }
    unsigned int getAsk_size() const { return ask_size; }
    double getOpen_price() const { return open_price; }
    double getClose_price() const { return close_price; }

    void setOutput_path(const std::string &output_path);
    const std::string &getSymbol() const;
    void setSymbol(const std::string &symbol);
    void on_message(std::unique_ptr<st_message>);
//    void set_strategy(instrument_observer *);
};


#endif //BRIMUS_INSTRUMENT_H
