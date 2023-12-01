#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input("inputPart1.txt");
  std::string line;
  int sum = 0;
  const int TENS = 10;
  const int ASCII_ZERO = static_cast<int>('0');

  if (!input.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  while (getline(input, line)) {
    int firstDigit = -1;
    int lastDigit = -1;

    for (char chr : line) {
      if (isdigit(chr) == 1) {
        if (firstDigit == -1) {
          firstDigit = static_cast<int>(chr) - ASCII_ZERO;
        }
        lastDigit = static_cast<int>(chr) - ASCII_ZERO;
      }
      if (firstDigit != -1) {
          if (lastDigit == -1) {
              lastDigit = firstDigit;
          }
      }
    }

    sum += firstDigit * TENS + lastDigit;
  }

  input.close();
  std::cout << "Total sum: " << sum << std::endl;
}
