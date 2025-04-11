#include "Item.h"
#include <iostream>

// Constructor implementation

Item::Item() : name(""), price(0.0f), type("") {}

Item::Item(const std::string& itemName, float itemPrice, const std::string& itemType)
    : name(itemName), price(itemPrice), type(itemType) {}

// Setters
void Item::setName(const std::string& itemName) {
    name = itemName;
}

void Item::setPrice(float itemPrice) {
    price = itemPrice;
}

void Item::setType(const std::string& itemType) {
    type = itemType;
}

void Item::setSize(const std::string& itemSize) {
    size = itemSize;
}

// Getters
std::string Item::getName() const {
    return name;
}

float Item::getPrice() const {
    return price;
}

std::string Item::getType() const {
    return type;
}

std::string Item::getSize() const {
    return size;
}

// Display method
void Item::display() const {
    if (type == "Drink") {
        std::cout << "Name: " << name
            << ", Price: £" << price
            << ", Size: " << size
            << std::endl;
    }
    else {
        std::cout << "Name: " << name
            << ", Price: £" << price
            << std::endl;
    }
}

std::string Item::toString() const {
    std::string result;
    if (size != "") {
        result = "Name: " + name +
            ", Price: £" + std::to_string(price) +
            ", Size: " + size;
    }
    else {
        result = "Name: " + name +
            ", Price: £" + std::to_string(price);
    }
    return result;
}


