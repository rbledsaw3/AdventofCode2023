#include <fstream>
#include <cmath>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

std::vector<int> parse_winning_numbers(const std::string& line) {
  std::vector<int> numbers;
  size_t start = line.find(':');
  size_t end = line.find('|');
  if (start != std::string::npos && end != std::string::npos) {
      start++;
      std::stringstream iss(line.substr(start, end - start));
      int number {0};
      while (iss >> number) {
          numbers.push_back(number);
      }
  }
  return numbers;
}

std::vector<int> parse_card_numbers(const std::string& line) {
  std::vector<int> numbers;
  size_t start = line.find('|');
  if (start != std::string::npos) {
      start++;
      std::stringstream iss(line.substr(start));
      int number {0};
      while (iss >> number) {
          numbers.push_back(number);
      }
  }
  return numbers;
}

int main() {
  std::ifstream file("inputDay4.txt");
  std::string line;
  int total = 0;

  while (std::getline(file, line)) {
      std::vector<int> left_numbers = parse_winning_numbers(line);
      std::vector<int> right_numbers = parse_card_numbers(line);
      std::set<int> right_set(right_numbers.begin(), right_numbers.end());

      int local_total = 0;
      int matches = -1;

      for (int num : left_numbers) {
        if (right_set.find(num) != right_set.end()) {
          matches++;
        }
        local_total = static_cast<int>( std::pow(2, matches) );
      }

      std::cout << "Card has total of " << local_total << " for matches." << std::endl;
      total += local_total;
  }

  std::cout << "Total for all cards: " << total << std::endl;
  return 0;
}
