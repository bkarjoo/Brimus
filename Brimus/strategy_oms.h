//
// Created by b.karjoo on 3/29/2017.
//

#ifndef BRIMUS_STRATEGY_OMS_H
#define BRIMUS_STRATEGY_OMS_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "order.h"
#include "execution.h"

class strategy_oms {
    // TODO : use a persistent database for orders to protect against sys crash
    std::map<std::string, std::vector<std::shared_ptr<order> > > open_orders;
    std::map<std::string, std::vector<std::shared_ptr<order> > > closed_orders;
    std::map<std::string, int> positions;
    std::map<std::string, std::vector<std::shared_ptr<execution> > > executions;
public:
    bool has_position(std::string symbol);
    bool has_open_orders(std::string symbol);
    int get_position(std::string symbol);
    double sum_money_flow(const std::vector<std::string>&);
    double sum_money_flow(std::string);
    double open_position_value();
    double open_position_value(std::string);
    double pandl();
    double pandl(std::string);

};


#endif //BRIMUS_STRATEGY_OMS_H
