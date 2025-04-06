#include "database.h"
#include <iostream>

Database::Database(const std::string& dbName) {
	if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
		open_result = sqlite3_errmsg(db);
	}
	else {
		open_result = "Database connected successfully!";
	}
}

Database::~Database() {
	sqlite3_close(db);
}


// Execute a SQL query
bool Database::executeQuery(const std::string& query) {
	char* errorMessage;
	if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
		execute_result = errorMessage;
		sqlite3_free(errorMessage);
		return false;
	}
	return true;
}


// Fetch all users
std::string Database::fetchUsers() {
    std::string result;
    const char* sql = "SELECT * FROM employees;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return "Error selecting data: " + std::string(sqlite3_errmsg(db));
    }

    result += "NAME | NUMBER  | ROLE\n";
    result += "----------------\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        result += 
            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))) + " | " +
            std::to_string(sqlite3_column_int(stmt, 2)) + " | " +
            std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))) + "\n";
    }

    sqlite3_finalize(stmt);
    return result;
}


// Fetch single user by name and employee number
std::tuple<std::string, int, std::string> Database::fetchUser(const std::string& name, int number) {
    const char* sql = "SELECT * FROM employees WHERE NAME = ? AND NUMBER = ?;";
    sqlite3_stmt* stmt;
    std::tuple<std::string, int, std::string> result;

    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return result = std::make_tuple("", 0, "");
    }

    // Bind parameters (name = ?, number = ?)
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, number);

    // Execute and fetch matching row(s)
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int number = sqlite3_column_int(stmt, 2);
        std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        result = std::make_tuple(name, number, role);
    } else {
        result = std::make_tuple("", 0, "");
    }

    // Clean up
    sqlite3_finalize(stmt);
    return result;
}
