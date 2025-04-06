
#include "Item.h"  // Include the base class header

class Drink : public Item {
private:
    std::string size;

public:
    Drink(const std::string& itemName, float itemPrice, const std::string& itemSize);
};
