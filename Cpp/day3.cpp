#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// function returns the indices of all symbols (anything that is not a number or a period) in a string
std::vector<int> get_symbol_indices(const std::string& line) {
  std::vector<int> indices;
  for (int i = 0; i < line.size(); ++i) {
    if (line[i] != '.' && std::isdigit(line[i]) == 0) {
      indices.push_back(i);
    }
  }
  return indices;
}

// function takes in an int for the vector index, an int for the position in the string in that vector, and the vector
// of strings to check. function returns a vector of ints that are the indices of the numbers that are up, down, left,
// right, or diagonal from the given index.
std::vector<std::pair<int, int>>
  get_adjacent_indices(const int& row, const int& col, const std::vector<std::string>& lines) {
  std::vector<std::pair<int, int>> adjacent_indices;

  // {-1, -1} | {-1, 0} | {-1, 1}
  // {0, -1}  | {0, 0}  | {0, 1}
  // {1, -1}  | {1, 0}  | {1, 1}

  // check up
  if (row > 0 && isdigit(lines[row - 1][col]) == 1) {
    adjacent_indices.emplace_back(row - 1, col);
  }
  // check down
  if (row < lines.size() - 1 && isdigit(lines[row + 1][col]) == 1) {
    adjacent_indices.emplace_back(row + 1, col);
  }
  // check left
  if (col > 0 && isdigit(lines[row][col - 1]) == 1) {
    adjacent_indices.emplace_back(row, col - 1);
  }
  // check right
  if (col < lines[row].size() - 1 && isdigit(lines[row][col + 1]) == 1) {
    adjacent_indices.emplace_back(row, col + 1);
  }
  // check diagonal up left
  if (row > 0 && col > 0 && isdigit(lines[row - 1][col - 1]) == 1) {
    adjacent_indices.emplace_back(row - 1, col - 1);
  }
  // check diagonal up right
  if (row > 0 && col < lines[row].size() - 1 && isdigit(lines[row - 1][col + 1]) == 1) {
    adjacent_indices.emplace_back(row - 1, col + 1);
  }
  // check diagonal down left
  if (row < lines.size() - 1 && col > 0 && isdigit(lines[row + 1][col - 1]) == 1) {
    adjacent_indices.emplace_back(row + 1, col - 1);
  }
  // check diagonal down right
  if (row < lines.size() - 1 && col < lines[row].size() - 1 && isdigit(lines[row + 1][col + 1]) == 1) {
    adjacent_indices.emplace_back(row + 1, col + 1);
  }

  return adjacent_indices;
}

// function takes in a vector of std::pairs<int, int> that are indices where a number is adjacent to a symbol and a
// vector of strings to check and looks left and right to find the continuous number and store that continuous number
// (left to right) in a vector of ints. function returns a vector of ints. example: if the vector of pairs is {(0, 3),
// (1, 2), (2, 6)} and the vector of strings is {"..123$..", ".!456..&", "..@.789.."}, then the function will return
// {123, 456, 789}
std::vector<int> get_continuous_numbers(const std::vector<std::pair<int, int>>& adjacent_indices,
                                        const std::vector<std::string>& lines) {
  std::set<std::pair<std::pair<int, int>, int>> unique_numbers;
  std::vector<int> continuous_numbers;

  for (const auto& pair : adjacent_indices) {
    int row = pair.first;
    int col = pair.second;

    while (col > 0 && isdigit(lines[row][col - 1]) == 1) {
      col--;
    }

    int start_col = col;

    std::string number;

    while (col < lines[row].size() && isdigit(lines[row][col]) == 1) {
      number += lines[row][col];
      col++;
    }

    if (!number.empty()) {
      int num = std::stoi(number);
      auto inserted = unique_numbers.insert({
        {row, start_col},
        num
      });
      if (inserted.second) {
        continuous_numbers.push_back(num);
      }
    }
  }
  return continuous_numbers;
}

std::vector<int> get_adjacent_numbers(const int& row, const int& col, const std::vector<std::string>& lines) {
    std::vector<int> adjacent_numbers;
    std::set<std::pair<int, int>> processed_starts; // To avoid processing the same number multiple times

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (const auto& direction : directions) {
        int new_row = row + direction.first;
        int new_col = col + direction.second;

        // Check bounds
        if (new_row < 0 || new_row >= lines.size() || new_col < 0 || new_col >= lines[new_row].size()) {
            continue;
        }

        // Check if the adjacent cell is a digit and hasn't been processed
        if (isdigit(lines[new_row][new_col]) == 1 && processed_starts.count({new_row, new_col}) == 0) {
            // Find the start of the number
            while (new_col > 0 && isdigit(lines[new_row][new_col - 1]) == 1) {
                new_col--;
            }

            // Check if this start has already been processed
            if (processed_starts.insert({new_row, new_col}).second) {
                std::string number;

                // Collect the entire number
                while (new_col < lines[new_row].size() && isdigit(lines[new_row][new_col]) == 1) {
                    number += lines[new_row][new_col];
                    new_col++;
                }

                if (!number.empty()) {
                    adjacent_numbers.push_back(std::stoi(number));
                }
            }
        }
    }
    return adjacent_numbers;
}


long calculate_gear_ratios(const std::vector<std::string>& lines) {
    long sum_gear_ratios { 0 };

    for (int row = 0; row < lines.size(); ++row) {
        for (int col = 0; col < lines[row].size(); ++col) {
            if (lines[row][col] == '*') {
                std::vector<int> adjacent_numbers = get_adjacent_numbers(row, col, lines);
                if (adjacent_numbers.size() == 2) {
                    sum_gear_ratios += static_cast<long>(adjacent_numbers[0]) * adjacent_numbers[1];
                }
            }
        }
    }
    return sum_gear_ratios;
}

int main(int argc, char* argv[]) {
  std::ifstream input_file(argv[1]);
  std::string line;
  std::vector<std::string> lines;
  std::vector<std::vector<int>> indices;
  std::vector<std::pair<int, int>> matches;
  while (std::getline(input_file, line)) {
    indices.push_back(get_symbol_indices(line));
    lines.push_back(line);
  }
  input_file.close();

  int count { 0 };
  for (auto it = indices.begin(); it != indices.end(); ++it) {
    for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
      std::vector<std::pair<int, int>> adjacent = get_adjacent_indices(count, *it2, lines);
      matches.insert(matches.end(), adjacent.begin(), adjacent.end());
    }
    count++;
  }
  std::vector<int> part_numbers = get_continuous_numbers(matches, lines);

  // sum all part numbers
  int sum { 0 };
  for (auto it = part_numbers.begin(); it != part_numbers.end(); ++it) {
    sum += *it;
  }
  std::cout << sum << std::endl;

  std::cout << "Part 2: Calculating gear ratios..." << std::endl;
  long sum_gear_ratios = calculate_gear_ratios(lines);
  std::cout << "Sum of all gear ratios: " << sum_gear_ratios << std::endl;

  return 0;
}
