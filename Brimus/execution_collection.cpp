//
// Created by b.karjoo on 4/10/2017.
//

#include "execution_collection.h"
using namespace std;

void execution_collection::add_execution(const execution& e) {
    add_execution(e.getQuantity(), e.getSymbol(), e.getPrice());
}

int execution_collection::execution_collection_size() const {
    return executions.size();
}

void execution_collection::add_execution(int exec_qty, std::string symbol, double price) {
    executions.push_back(execution(exec_qty,symbol,price));
}

void execution_collection::add_execution(int execQty, std::string symbol, double price, std::string id) {
    executions.push_back(execution(execQty,symbol,price,id));
}

double execution_collection::last_buy_fill_price(const string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
        [&symbol](const execution& e){
                return e.getSymbol() == symbol && e.getQuantity() > 0;
        });
    if (it != executions.rend()) return it->getPrice();
    else
        return 0;
}

double execution_collection::last_sell_fill_price(const std::string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
                      [&symbol](const execution& e){
                          return e.getSymbol() == symbol && e.getQuantity() < 0;
                      });
    if (it != executions.rend()) return it->getPrice();
    else
        return 0;
}

double execution_collection::last_fill_price(const std::string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
                      [&symbol](const execution& e){
                          return e.getSymbol() == symbol;
                      });
    if (it != executions.rend()) return it->getPrice();
    else
        return 0;
}

double execution_collection::sum_money_flow() const {
    double sum;
    for (auto& a : executions) {
        sum += a.money_flow();
    }
    return sum;
}

double execution_collection::sum_money_flow(std::string symbol) const {
    double sum;
    for (auto& a : executions) {
        if (a.getSymbol() == symbol) sum += a.money_flow();
    }
    return sum;
}

int execution_collection::sum_executions(const std::string &id) const {
    int sum;
    for (auto& a : executions) {
        if (a.getId() == id) sum += a.getQuantity();
    }
    return sum;
}




