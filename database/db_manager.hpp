#pragma once
#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
  DatabaseManager(const std::string &dbPath);

  ~DatabaseManager();

  DatabaseManager(const DatabaseManager &) = delete;
  DatabaseManager &operator=(const DatabaseManager &) = delete;

  bool executeQuery(const std::string &sql);

private:
  sqlite3 *ticker_db = nullptr;
};
