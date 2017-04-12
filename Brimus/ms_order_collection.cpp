//
// Created by b.karjoo on 4/11/2017.
//

#include "ms_order_collection.h"

void ms_order_collection::add_order(std::unique_ptr<ms_order> order) {
    orders.push_back(move(order));
}

int ms_order_collection::size() const {
    return orders.size();
}

ms_order_collection::order_ptr ms_order_collection::remove_order(const std::string &id) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if ((*it)->getId() == id) {
            auto ret = move(*it);
            orders.erase(it);
            return move(ret);
        }
    }
    return nullptr;
}

const std::unique_ptr<ms_order>& ms_order_collection::get_order(const std::string &id) {
    std::vector<std::unique_ptr<ms_order>>::iterator it =
            std::find_if(orders.begin(), orders.end(),
                      [&id](const std::unique_ptr<ms_order>& op)
                      { return op->getId() == id; });
    return *it;
}


