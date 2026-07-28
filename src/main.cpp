#include <iostream>
#include <vector>

class Stock {
private:
  double price;
  std::string ticker;

public:
  // Getter and Setter Methods for Stock class
  void set_price(double new_price) { price = new_price; }
  void set_ticker(std::string new_ticker) { ticker = new_ticker; }
  double get_price() { return price; }
  std::string get_ticker() { return ticker; }
};

int main() {

  std::vector<Stock> Stocks(0);
  Stock s1;

  s1.set_price(100);
  s1.set_ticker("APPL");

  std::string ticker_s1 = s1.get_ticker();
  double price_s1 = s1.get_price();

  std::cout << "Ticker: " << ticker_s1 << " Price: " << price_s1 << std::endl;

  return 0;
}
