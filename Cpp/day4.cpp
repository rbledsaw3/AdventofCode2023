#include <cmath>
#include <fstream>
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
    int number { 0 };
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
    int number { 0 };
    while (iss >> number) {
      numbers.push_back(number);
    }
  }
  return numbers;
}

int main() {
  std::ifstream file("inputDay4.txt");
  std::string line;
  int part1_total = 0;
  int part2_total = 0;
  int card_number = 1;
  std::vector<int> card_points;
  std::vector<int> card_matches;
  std::vector<int> card_copies;

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
      local_total = static_cast<int>(std::pow(2, matches));
    }

    part1_total += local_total;
    card_points.push_back(local_total);
    card_matches.push_back(matches + 1);
    card_copies.push_back(1);
    std::cout << "Card " << card_number << " has total of "
        << local_total << " for matches. card_matches[" << card_number - 1
        << "] = " << matches + 1 << "." << std::endl;
  }

  for (int i = 0; i < static_cast<int>(card_matches.size()); i++) {
      int count = card_copies[i];
      while (count > 0) {
          if (card_matches[i] == 0) {
              break;
          }
          for (int j = card_matches[i]; j > 0; j--) {
            card_copies[i + j]++;
          }
          count--;
      }
  }

  for (int num : card_copies) {
      part2_total += num;
  }

  std::cout << "Total for all cards: " << part1_total << std::endl;
  std::cout << "Total for all cards with copies: " << part2_total << std::endl;
  return 0;
}
