#pragma once

#include <unordered_map>
#include <tuple>
#include <string>

class ProductMap {

public:
	static std::tuple<std::string, float, std::string, std::string> getProduct(int ID);

private:
	static const std::unordered_map<int, std::tuple<std::string, float, std::string, std::string>> product_map;
};