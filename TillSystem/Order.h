#pragma once

#include <vector>
#include "Item.h"

class Order {
public:

    void addItem(const Item& item);
    void removeRecent();
    void removeSelected(int index);
    void clearOrder();
    std::string printOrder() const;
    std::string printFirst() const;
    int getSize();
    float getItemPrice(int index);

private:
    std::vector<Item> items;
};
