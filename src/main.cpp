#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
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

std::string format_price(const double price) {
  std::ostringstream formatted;
  formatted << std::fixed << std::setprecision(2) << price;
  return formatted.str();
}

void print_stocks(const std::unordered_map<std::string, double> &stocks) {
  std::vector<std::pair<std::string, double>> sorted_stocks(stocks.begin(),
                                                            stocks.end());
  std::sort(sorted_stocks.begin(), sorted_stocks.end(),
            [](const auto &left, const auto &right) {
              return left.first < right.first;
            });

  const std::string ticker_header = "Ticker";
  const std::string price_header = "Price ($)";
  std::size_t ticker_width = ticker_header.size();
  std::size_t price_width = price_header.size();

  for (const auto &[ticker, price] : sorted_stocks) {
    ticker_width = std::max(ticker_width, ticker.size());
    price_width = std::max(price_width, format_price(price).size());
  }

  const auto print_border = [&]() {
    std::cout << '+' << std::string(ticker_width + 2, '-')
              << '+' << std::string(price_width + 2, '-') << "+\n";
  };

  print_border();
  std::cout << "| " << std::left << std::setw(ticker_width) << ticker_header
            << " | " << std::right << std::setw(price_width) << price_header
            << " |\n";
  print_border();

  for (const auto &[ticker, price] : sorted_stocks) {
    std::cout << "| " << std::left << std::setw(ticker_width) << ticker << " | "
              << std::right << std::setw(price_width) << format_price(price)
              << " |\n";
  }

  print_border();
}

// Main Fnctionality
int main() {
#ifdef DEV
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(1, 100);

  int percent = distribution(generator);

#endif

  std::unordered_map<std::string, double> Stocks;

  Stocks["AAPL"] = 102.3;
  Stocks["NVDA"] = 123.4;
  Stocks["ABC"] = 1000.4;
  Stocks["XYZ"] = 1.2;
  Stocks["AAAA"] = 103.4;

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
      print_stocks(Stocks);
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
