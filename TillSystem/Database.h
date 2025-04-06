#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite/sqlite3.h"

class Database {
public:
	Database(const std::string& dbName);
	~Database();
	bool executeQuery(const std::string& query);
	std::string fetchUsers();
	std::string fetchProducts();
	std::tuple<std::string, int, std::string> fetchUser(const std::string& name, int number);

private:
	sqlite3* db;
	std::string open_result;
	std::string execute_result;
};

#endif // DATABASE_H