#pragma once

#include <string>

class Item {
public:

    // Constructor
    Item();
    Item(const std::string& itemName, float itemPrice, const std::string& itemType);

    // Setters
    void setName(const std::string& itemName);
    void setPrice(float itemPrice);
    void setType(const std::string& itemType);
    void setSize(const std::string& itemSize);

    // Getters
    std::string getName() const;
    float getPrice() const;
    std::string getType() const;
    std::string getSize() const;

    // Utility
    void display() const;
    std::string toString() const;

private:
    std::string name;
    float price;
    std::string type;
    std::string size;
};
