#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

const int ASCII_ZERO = static_cast<int>('0');

int findNumber(const std::string& line, const std::unordered_map<std::string, char>& wordMap, bool searchFromStart) {
  if (line.empty()) {
    return -1;
  }

  int index = searchFromStart ? 0 : static_cast<int>(line.size()) - 1;
  int increment = searchFromStart ? 1 : -1;

  while (searchFromStart ? (index < line.size()) : (index >= 0)) {
    if (std::isdigit(line[index]) == 1) {
      return line[index] - ASCII_ZERO;
    }

    std::string currentWord;
    for (int i = index; searchFromStart ? (i < line.size()) : (i >= 0); i += increment) {
      currentWord = searchFromStart ? (line.substr(index, i - index + 1)) : (line.substr(i, index - i + 1));
      std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

      auto itr = wordMap.find(currentWord);
      if (itr != wordMap.end()) {
        return itr->second - '0';
      }

      if (std::isalpha(line[i]) == 0) {
        break;
      }
    }
    index += increment;
  }
  return -1;
}

std::string processLine(const std::string& line) {
  static const std::unordered_map<std::string, char> wordMap = {
    {  "one", '1'},
    {  "two", '2'},
    {"three", '3'},
    { "four", '4'},
    { "five", '5'},
    {  "six", '6'},
    {"seven", '7'},
    {"eight", '8'},
    { "nine", '9'},
  };

  int firstNumber = findNumber(line, wordMap, true);
  int lastNumber = findNumber(line, wordMap, false);

  return firstNumber != -1 && lastNumber != -1 ? std::to_string(firstNumber) + std::to_string(lastNumber) : "";
}

int main() {
  std::ifstream input("input.txt");
  std::string line;
  int sum = 0;

  if (!input.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  while (getline(input, line)) {
    std::cout << line << std::endl;
    std::string processedLine = processLine(line);
    std::cout << processedLine << std::endl;

    if (!processedLine.empty()) {
      sum += std::stoi(processedLine);
    }
    std::cout << sum << std::endl;
  }

  input.close();
  std::cout << "Total sum: " << sum << std::endl;

  return 0;
}
