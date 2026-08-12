#include "db_manager.hpp"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &db_path) {
  if (sqlite3_open(db_path.c_str(), &ticker_db) != SQLITE_OK) {
    std::cerr << "Failed to open DB: " << sqlite3_errmsg(ticker_db)
              << std::endl;
  }
}

DatabaseManager::~DatabaseManager() {
  if (ticker_db) {
    sqlite3_close(ticker_db);
  }
}

bool DatabaseManager::executeQuery(const std::string &sql) {
  char *error_message = nullptr;
  int rc =
      sqlite3_exec(ticker_db, sql.c_str(), nullptr, nullptr, &error_message);

  if (rc != SQLITE_OK) {
    std::cerr << "SQL Error: " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }
  return true;
}
