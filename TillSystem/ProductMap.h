#pragma once

#include <unordered_map>
#include <tuple>
#include <string>

enum class Type : uint8_t {
    Drink = 0,
    Food = 1,
    Addon = 2,
    Merch = 3,
    NULL_RETURN = 4
};

enum class Size : uint8_t {
    NA = 0,
    SML = 1,
    MED = 2,
    LRG = 3,
    NULL_RETURN = 4
};

class ProductMap {

public:
	std::tuple<std::string, float, Type, Size> getProduct(int ID);
    static std::string typeToString(const Type type);
    static std::string sizeToString(const Size size);

private:
    const std::unordered_map<int, std::tuple<std::string, float, Type, Size>> product_map = {
        {1000, {"Americano", 2.80, Type::Drink, Size::SML}},
        {1001, {"Americano", 3.00, Type::Drink, Size::MED}},
        {1002, {"Americano", 3.20, Type::Drink, Size::LRG}},
        {1003, {"Americano w/ Milk", 3.20, Type::Drink, Size::SML}},
        {1004, {"Americano w/ Milk", 3.40, Type::Drink, Size::MED}},
        {1005, {"Americano w/ Milk", 3.60, Type::Drink, Size::LRG}},
        {1006, {"Latte", 3.20, Type::Drink, Size::SML}},
        {1007, {"Latte", 3.40, Type::Drink, Size::MED}},
        {1008, {"Latte", 3.60, Type::Drink, Size::LRG}},
        {1009, {"Cappuccino", 3.20, Type::Drink, Size::SML}},
        {1010, {"Cappuccino", 3.40, Type::Drink, Size::MED}},
        {1011, {"Cappuccino", 3.60, Type::Drink, Size::LRG}},
        {1012, {"Mocha", 3.40, Type::Drink, Size::SML}},
        {1013, {"Mocha", 3.60, Type::Drink, Size::MED}},
        {1014, {"Mocha", 3.80, Type::Drink, Size::LRG}},
        {1015, {"Flat White", 3.20, Type::Drink, Size::SML}},
        {1016, {"Flat Black", 3.00, Type::Drink, Size::SML}},
        {1017, {"Iced Americano", 2.80, Type::Drink, Size::SML}},
        {1018, {"Iced Americano", 3.00, Type::Drink, Size::MED}},
        {1019, {"Iced Americano", 3.20, Type::Drink, Size::LRG}},
        {1020, {"Iced Latte", 3.20, Type::Drink, Size::SML}},
        {1021, {"Iced Latte", 3.40, Type::Drink, Size::MED}},
        {1022, {"Iced Latte", 3.60, Type::Drink, Size::LRG}},
        {1023, {"Iced Cappuccino", 3.20, Type::Drink, Size::SML}},
        {1024, {"Iced Cappuccino", 3.40, Type::Drink, Size::MED}},
        {1025, {"Iced Cappuccino", 3.60, Type::Drink, Size::LRG}},
        {1026, {"Iced Mocha", 3.40, Type::Drink, Size::SML}},
        {1027, {"Iced Mocha", 3.60, Type::Drink, Size::MED}},
        {1028, {"Iced Mocha", 3.80, Type::Drink, Size::LRG}},
        {1029, {"Iced Flat White", 3.20, Type::Drink, Size::SML}},
        {1030, {"Iced Flat Black", 3.00, Type::Drink, Size::SML}},
        {1031, {"Breakfast Tea", 2.60, Type::Drink, Size::NA}},
        {1032, {"Decaf Tea", 2.60, Type::Drink, Size::NA}},
        {1033, {"Earl Grey Tea", 2.60, Type::Drink, Size::NA}},
        {1034, {"Mint Tea", 2.60, Type::Drink, Size::NA}},
        {1035, {"Green Tea", 2.60, Type::Drink, Size::NA}},
        {1036, {"Berry Tea", 2.60, Type::Drink, Size::NA}},
        {1037, {"Hot Chocolate", 3.40, Type::Drink, Size::SML}},
        {1038, {"Hot Chocolate", 3.60, Type::Drink, Size::MED}},
        {1039, {"Hot Chocolate", 3.80, Type::Drink, Size::LRG}},
        {1040, {"White Hot Chocolate", 3.40, Type::Drink, Size::SML}},
        {1041, {"White Hot Chocolate", 3.60, Type::Drink, Size::MED}},
        {1042, {"White Hot Chocolate", 3.80, Type::Drink, Size::LRG}},
        {1043, {"Chai Latte", 3.20, Type::Drink, Size::SML}},
        {1044, {"Chai Latte", 3.40, Type::Drink, Size::MED}},
        {1045, {"Chai Latte", 3.60, Type::Drink, Size::LRG}},
        {1046, {"Coffee w/ Cream Frappe", 4.20, Type::Drink, Size::SML}},
        {1047, {"Coffee w/ Cream Frappe", 4.40, Type::Drink, Size::MED}},
        {1048, {"Strawberry and Cream Frappe w/ Coffee", 4.20, Type::Drink, Size::SML}},
        {1049, {"Strawberry and Cream Frappe w/ Coffee", 4.40, Type::Drink, Size::MED}},
        {1050, {"Strawberry and Cream Frappe", 4.00, Type::Drink, Size::SML}},
        {1051, {"Strawberry and Cream Frappe", 4.20, Type::Drink, Size::MED}},
        {1052, {"Salted Caramel Frappe w/ Coffee", 4.20, Type::Drink, Size::SML}},
        {1053, {"Salted Caramel Frappe w/ Coffee", 4.40, Type::Drink, Size::MED}},
        {1054, {"Salted Caramel Frappe", 4.00, Type::Drink, Size::SML}},
        {1055, {"Salted Caramel Frappe", 4.20, Type::Drink, Size::MED}},
        {1056, {"Chocolate Fudge Brownie Frappe w/ Coffee", 4.40, Type::Drink, Size::SML}},
        {1057, {"Chocolate Fudge Brownie Frappe w/ Coffee", 4.60, Type::Drink, Size::MED}},
        {1058, {"Chocolate Fudge Brownie Frappe", 4.20, Type::Drink, Size::SML}},
        {1059, {"Chocolate Fudge Brownie Frappe", 4.40, Type::Drink, Size::MED}},
        {1060, {"Mango Bubble Frappe", 4.00, Type::Drink, Size::SML}},
        {1061, {"Mango Bubble Frappe", 4.20, Type::Drink, Size::MED}},
        {1062, {"Peach Ice Tea", 2.40, Type::Drink, Size::SML}},
        {1063, {"Peach Ice Tea", 2.60, Type::Drink, Size::MED}},
        {1064, {"Mango and Passion Fruit Cooler", 3.00, Type::Drink, Size::SML}},
        {1065, {"Mango and Passion Fruit Cooler", 3.20, Type::Drink, Size::MED}},
        {1066, {"Red Berry Cooler", 3.00, Type::Drink, Size::SML}},
        {1067, {"Red Berry Cooler", 3.20, Type::Drink, Size::MED}},
        {1068, {"Coca-Cola™", 2.20, Type::Drink, Size::NA}},
        {1069, {"Coca-Cola™ Diet", 2.20, Type::Drink, Size::NA}},
        {1070, {"Coca-Cola™ Zero", 2.20, Type::Drink, Size::NA}},
        {1071, {"Irn Bru™", 2.20, Type::Drink, Size::NA}},
        {1072, {"Irn Bru™ Sugar Free", 2.20, Type::Drink, Size::NA}},
        {1073, {"Fanta™", 2.20, Type::Drink, Size::NA}},
        {1074, {"Sprite", 2.20, Type::Drink, Size::NA}},
        {1075, {"Smart Water™", 2.20, Type::Drink, Size::NA}},
        {1076, {"Smart Water™ Sparkling", 2.20, Type::Drink, Size::NA}}
    };

};