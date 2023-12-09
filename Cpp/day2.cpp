#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;
const int PADDING = 5;

struct CubeCounts {
    int red;
    int green;
    int blue;
};

std::vector<std::string> split(const std::string &str, char delim) {
    std::vector<std::string> result;
    std::istringstream stream(str);
    std::string item;
    while (getline(stream, item, delim)) {
        result.push_back(item);
    }
    return result;
}

CubeCounts parseCounts(const std::string &str) {
    std::istringstream iss(str);
    std::string token;
    CubeCounts counts{0, 0, 0};

    while (iss >> token) {
        int num {0};
        std::string color;
        std::istringstream tokenStream(token);
        tokenStream >> num >> color;
        if (color.find("red") != std::string::npos) {
            counts.red = num;
        }
        else if (color.find("green") != std::string::npos) {
            counts.green = num;
        }
        else if (color.find("blue") != std::string::npos) {
            counts.blue = num;
        }
    }

    return counts;
}

int main() {
    std::ifstream file("inputDay2.txt");
    std::string line;
    int sumOfIdsPart1 = 0;
    int totalPower = 0;

    while (std::getline(file, line)) {
        size_t colonPos = line.find(':');
        int gameId = std::stoi(line.substr(PADDING, colonPos - PADDING));
        std::string data = line.substr(colonPos + 2);

        std::vector<std::string> sets = split(data, ';');
        CubeCounts maxCounts{0, 0, 0};
        bool isValidForPart1 = true;

        for (const auto &set : sets) {
            CubeCounts counts = parseCounts(set);
            maxCounts.red = std::max(maxCounts.red, counts.red);
            maxCounts.green = std::max(maxCounts.green, counts.green);
            maxCounts.blue = std::max(maxCounts.blue, counts.blue);

            if (counts.red > MAX_RED || counts.green > MAX_GREEN || counts.blue > MAX_BLUE) {
                isValidForPart1 = false;
                break;
            }
        }

        if (isValidForPart1) {
            sumOfIdsPart1 += gameId;
        }

        totalPower += (maxCounts.red * maxCounts.green * maxCounts.blue);
    }

    std::cout << "Sum of IDs for Part 1: " << sumOfIdsPart1 << std::endl;
    std::cout << "Total power for Part 2: " << totalPower << std::endl;

    return 0;
}
