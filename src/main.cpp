#include "../database/db_manager.hpp"
#include <curl/curl.h>
#include <iostream>
#include <random>
#include <unordered_map>
#define DEV

class Stock {

private:
  double price;
  std::string ticker;

public:
  // Getter and Setter Methods for Stock class
  void set_price(const double new_price) { price = new_price; }
  void set_ticker(const std::string &new_ticker) { ticker = new_ticker; }
  double get_price() { return price; }
  std::string get_ticker() { return ticker; }
  bool operator==(const Stock &other) const { return ticker == other.ticker; }

  friend std::ostream &operator<<(std::ostream &, const Stock &);
  friend std::istream &operator>>(std::istream &, Stock &);
};

// Overloading << and >> for os and is for Stock class
std::ostream &operator<<(std::ostream &os, const Stock &stock) {
  os << stock.ticker << ' ' << stock.price;
  return os;
}

std::istream &operator>>(std::istream &is, Stock &stock) {
  is >> stock.ticker >> stock.price;
  return is;
}

// Main Fnctionality
int main() {
#ifdef DEV
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(1, 100);

  int percent = distribution(generator);

#endif
  DatabaseManager db("ticker_display.db");
  static const char *create_sql_table = "CREATE TABLE IF NOT EXISTS STOCKS("
                                        "TICKER TEXT NOT NULL UNIQUE"
                                        "PRICE FLOAT NOT NULL);";

  db.executeQuery(create_sql_table);

  std::unordered_map<std::string, double> Stocks;

  Stocks["AAPL"] = 102.3;
  Stocks["NVDA"] = 123.4;
  Stocks["ABC"] = 1000.4;
  Stocks["XYZ"] = 1.2;
  Stocks["AAAA"] = 103.4;

  auto print_umap = [](const auto &key, const auto &value) {
    std::cout << "Ticker:[" << key << "] Value:[" << value << "]\n";
  };

  bool game_on = true;
  // Intro message for display
  std::cout << "Welcome to Ticker Display\n"
            << "What would you like to do?\n1) Display Stocks\n2) Add "
               "Stock\n3) Delete Stock\nq) Quit\n";
  while (game_on) {
    char input = 0;
    std::cout << "Input: ";
    std::cin >> input;

    switch (input) {
    case '1':
      for (const std::pair<std::string, double> &ticker : Stocks) {
        print_umap(ticker.first, ticker.second);
      }
      break;
    case '2': {
      std::string ticker;
      double price;
      std::cout << "Enter Ticker (ABCD): \n";
      std::cin >> ticker;
      std::cout << "Price: \n";
      std::cin >> price;

      Stocks[ticker] = price;
      std::cout << "Success!!\n";
      break;
    }
    case '3': {
      std::cout << "What is the Ticker of the stock you want to delete?\n";
      std::string del_ticker;
      std::cin >> del_ticker;
      Stocks.erase(del_ticker);
      std::cout << "Success!!\n";
      break;
    }
    case 'q':
      std::cout << "Turning Off...\n";
      game_on = false;
      break;
    }
  }
  return 0;
}
