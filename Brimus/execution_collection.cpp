//
// Created by b.karjoo on 4/10/2017.
//

#include "execution_collection.h"
using namespace std;

void execution_collection::add_execution(execution_collection::exec_ptr e) {
    executions.push_back(move(e));
}

int execution_collection::execution_collection_size() const {
    return executions.size();
}

void execution_collection::add_execution(int exec_qty, std::string symbol, double price) {
    auto ptr = make_unique<execution>(exec_qty,symbol,price);
    executions.push_back(move(ptr));
}

double execution_collection::last_buy_fill_price(const string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
        [&symbol](const exec_ptr& e){
                return e->getSymbol() == symbol && e->getQuantity() > 0;
        });
    if (it != executions.rend()) return it->get()->getPrice();
    else
        return 0;
}

double execution_collection::last_sell_fill_price(const std::string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
                      [&symbol](const exec_ptr& e){
                          return e->getSymbol() == symbol && e->getQuantity() < 0;
                      });
    if (it != executions.rend()) return it->get()->getPrice();
    else
        return 0;
}

double execution_collection::last_fill_price(const std::string &symbol) const {
    auto it = find_if(executions.rbegin(),executions.rend(),
                      [&symbol](const exec_ptr& e){
                          return e->getSymbol() == symbol;
                      });
    if (it != executions.rend()) return it->get()->getPrice();
    else
        return 0;
}

double execution_collection::sum_money_flow() const {
    double sum;
    for (auto& a : executions) {
        sum += a->money_flow();
    }
    return sum;
}

double execution_collection::sum_money_flow(std::string symbol) const {
    double sum;
    for (auto& a : executions) {
        if (a->getSymbol() == symbol) sum += a->money_flow();
    }
    return sum;
}


