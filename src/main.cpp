#include <algorithm>
#include <iostream>
#include <vector>

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

std::ostream &operator<<(std::ostream &os, const Stock &stock) {
  os << stock.ticker << ' ' << stock.price;
  return os;
}

std::istream &operator>>(std::istream &is, Stock &stock) {
  is >> stock.ticker >> stock.price;
  return is;
}

int main() {

  std::vector<Stock> stocks;

  // Intro message for display
  std::cout << "\n\nHello, Welcome to my Stock Ticker Display!\nWhat would you "
               "like to "
               "do?:\n\n1:) Display Stocks\n2:) Add Stock\n\n(Press q to quit)"
            << std::endl;

  int input;
  std::cin >> input;

  switch (input) {
  case 1:
    for (int i = 0; i < stocks.size(); ++i) {
      std::cout << stocks[i];
    }
  case 2:
    Stock stock;

    if (!(std::cin >> stock)) {
      std::cout << "Error: Not a valid input.\n";
    } else if (std::find(stocks.begin(), stocks.end(), stock) != stocks.end()) {
      std::cout << "Error: Duplicate Stock!!!";
    } else {
      stocks.push_back(stock);
    }
  }

  return 0;
}
