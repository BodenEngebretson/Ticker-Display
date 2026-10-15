#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#define DEV

enum class Side { Buy, Sell }; // Makes a type that could either be Buy or Sell

// Creates a data type for Order
struct Order {
  std::string ticker;
  double price;
  Side side;
  int quantity;
  int remaining_quantity;
};

// Formats the price to a precision of 2
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
    std::cout << '+' << std::string(ticker_width + 2, '-') << '+'
              << std::string(price_width + 2, '-') << "+\n";
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

void submit_order(Order order, std::vector<Order> &buy_orders,
                  std::vector<Order> &sell_orders) {
  if (order.side == Side::Buy) {
    for (Order &Sell_Order : sell_orders) {
      if (Sell_Order.ticker == order.ticker) {
        if (order.remaining_quantity == 0) {
          break;
        }
        if (order.price >= Sell_Order.price) {
          int traded_amount;
          traded_amount =
              std::min(order.remaining_quantity, Sell_Order.remaining_quantity);
          Sell_Order.remaining_quantity =
              Sell_Order.remaining_quantity - traded_amount;
          order.remaining_quantity = order.remaining_quantity - traded_amount;
        }
      }
    }
    if (order.remaining_quantity > 0) {
      buy_orders.push_back(order);
    }
  } else if (order.side == Side::Sell) {
    for (Order &Buy_Order : buy_orders) {
      if (order.remaining_quantity == 0) {
        break;
      }
      if (order.price <= Buy_Order.price) {
        int traded_amount;
        traded_amount =
            std::min(order.remaining_quantity, Buy_Order.remaining_quantity);
        Buy_Order.remaining_quantity =
            Buy_Order.remaining_quantity - traded_amount;
        order.remaining_quantity = order.remaining_quantity - traded_amount;
        if (order.remaining_quantity > 0) {
          sell_orders.push_back(order);
        }
      }
    }
  }
}
// Main Fnctionality
int main() {
  Order order1;
  order1.ticker = "AAPL";
  order1.price = 103.4;
  order1.side = Side::Buy;
  order1.quantity = 6;
  order1.remaining_quantity = order1.quantity;

  Order order2;
  order2.ticker = "AAPL";
  order2.price = 103.0;
  order2.side = Side::Sell;
  order2.quantity = 5;
  order2.remaining_quantity = order2.quantity;

  std::vector<Order> incoming_orders;
  std::vector<Order> buy_orders;
  std::vector<Order> sell_orders;

  incoming_orders.push_back(order1);
  incoming_orders.push_back(order2);

  for (const Order &order : incoming_orders) {
    submit_order(order, buy_orders, sell_orders);
    std::cout << "Success?!" << std::endl;
  }

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
