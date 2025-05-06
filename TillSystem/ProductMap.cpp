#include "ProductMap.h"

std::tuple<std::string, float, Type, Size> ProductMap::getProduct(int ID) {
    auto it = product_map.find(ID);
    if (it != product_map.end()) {
        return it->second;
    }
    return { "", 0.0f, Type::NULL_RETURN, Size::NULL_RETURN };
}

std::string ProductMap::typeToString(const Type type) {
    switch (type) {
    case Type::Drink:
        return "Drink";
        break;
    case Type::Food:
        return "Food";
        break;
    case Type::Addon:
        return "Addon";
        break;
    case Type::Merch:
        return "Merch";
        break;
    default: return "";
    }
}

std::string ProductMap::sizeToString(const Size size) {
    switch (size) {
    case Size::NA:
        return "";
        break;
    case Size::SML:
        return "SML";
        break;
    case Size::MED:
        return "MED";
        break;
    case Size::LRG:
        return "LRG";
        break;
    default: return "";
    }
}