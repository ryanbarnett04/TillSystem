#pragma once

#include <string>
#include "ProductMap.h"

class Item {
public:

    // Constructor
    Item();
    Item(const std::string& itemName, float itemPrice, Type itemType, Size itemSize);

    // Setters
    void setName(const std::string& itemName);
    void setPrice(const float itemPrice);
    void setType(const Type itemType);
    void setSize(const Size itemSize);

    // Getters
    std::string getName() const;
    float getPrice() const;
    Type getType() const;
    Size getSize() const;

    // Utility
    void display() const;
    std::string toString() const;

private:
    std::string name;
    float price;
    Type type;
    Size size;
};
