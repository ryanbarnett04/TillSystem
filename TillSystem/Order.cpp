#include "Order.h"
#include <iostream>

void Order::addItem(const Item& item) {
    items.push_back(item);
}

void Order::removeRecent() {
    if (items.size() != 0) {
        items.pop_back();
    }
    else {
        return;
    }
}

void Order::removeSelected(int index) {
    items.erase(items.begin() + index);
}

void Order::clearOrder() {
    items.clear();
}

std::string Order::printOrder() const {
    if (items.empty()) {
        return "The order is empty.";
    }
    std::string orderDetails = "Order Details:\n";
    for (const Item& item : items) {
        orderDetails += item.toString() + "\n";
    }
    return orderDetails;
}

std::string Order::printFirst() const {
    Item firstItem = items[0];
    std::string printFirst = firstItem.toString();
    return printFirst;
}
