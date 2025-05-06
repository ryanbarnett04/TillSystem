#include "Item.h"
#include <iostream>

// Constructor implementation

Item::Item() : name(""), price(0.0f), type(Type::NULL_RETURN) {}

Item::Item(const std::string& itemName, float itemPrice, const Type itemType, const Size itemSize)
    : name(itemName), price(itemPrice), type(itemType), size(itemSize) {}

// Setters
void Item::setName(const std::string& itemName) {
    name = itemName;
}

void Item::setPrice(float itemPrice) {
    price = itemPrice;
}

void Item::setType(const Type itemType) {
    type = itemType;
}

void Item::setSize(const Size itemSize) {
    size = itemSize;
}

// Getters
std::string Item::getName() const {
    return name;
}

float Item::getPrice() const {
    return price;
}

Type Item::getType() const {
    return type;
}

Size Item::getSize() const {
    return size;
}

// Display method
void Item::display() const {
    if (type == Type::Drink) {
        std::cout << "Name: " << name
            << ", Price: £" << price
            << ", Size: " << ProductMap::sizeToString(size)
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
    if (size != Size::NA) {
        result = "Name: " + name +
            ", Price: £" + std::to_string(price) +
            ", Size: " + ProductMap::sizeToString(size);
    }
    else {
        result = "Name: " + name +
            ", Price: £" + std::to_string(price);
    }
    return result;
}


