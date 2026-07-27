#include <iostream>

inline void keep_window_open() {
  char ch;
  std::cin >> ch;
}

int main() {

  int Bodens_Age = 20;

  std::cout << "what is your name and age?:\n";

  std::string name = " ";
  int age = 0;

  std::cin >> name >> age;

  switch (age) {
  case 20:
    if (name == "Boden")
      std::cout << "Hello Admin!\n";
    else
      break;
  default:
    std::cout << "Hello, " << name << "\nYour age is: " << age << std::endl;
  }

  int i = 0;

  while (i < 26) {

    char letter = 'a' + i;
    int val = 'a' + i;

    std::cout << letter << "\t" << val << std::endl;
    ++i;
  }

  return 0;
}
