#include <iostream>
#include <string>
#include <fstream>

int part1()
{
  std::ifstream file("input.txt");
  int total = 0;

  // Go through all lines
  for (std::string line; std::getline(file, line);) {
    std::string value;

    // Iterate from start to end to find first digit
    for (auto it = line.begin(); it != line.end(); ++it) {
      // Check for digit
      if (*it >= '0' && *it <= '9') {
        value += *it;
        break;
      }
    }

    // Iterate from end to start to find second digit
    for (auto it = line.rbegin(); it != line.rend(); ++it) {
      // Check for digit
      if (*it >= '0' && *it <= '9') {
        value += *it;
        break;
      }
    }

    // Convert value from string to int
    total += std::stoi(value, nullptr, 10);
  }

  return total;
}

int part2()
{
  std::ifstream file("input.txt");
  int total = 0;
  std::pair<std::string, char> numbers[] = {
    {"one",   '1'},
    {"two",   '2'},
    {"three", '3'},
    {"four",  '4'},
    {"five",  '5'},
    {"six",   '6'},
    {"seven", '7'},
    {"eight", '8'},
    {"nine",  '9'}
  };

  // Iterate all lines
  for (std::string line; std::getline(file, line);) {
    std::string value;
    for (int i = 0; i < line.length(); ++i) {
      // Look for digit from start
      if (line[i] >= '0' && line[i] <= '9') {
        value += line[i];
      } else {
        // If no digit is found, look for digit string
        for (auto it : numbers) {
          // Find string from position
          if (line.find(it.first, i) == i) {
            value += it.second;
            break;
          }
        }
      }

      // Found first digit
      if (value.length() > 0)
        break;
    }
    for (int i = 0; i < line.length(); ++i) {
      int index = line.length() - i - 1;

      // Look for digit from end
      if (line[index] >= '0' && line[index] <= '9') {
        value += line[index];
      } else {
        // If no digit is found, look for digit strings
        for (auto it : numbers) {
          // Find string from end
          if (line.find(it.first, index) != std::string::npos) {
            value += it.second;
            break;
          }
        }
      }

      // Found second digit
      if (value.length() > 1)
        break;
    }
    total += std::stoi(value, nullptr, 10);
  }

  return total;
}

int main(int argc, char *argv[])
{
  std::cout << "part1: " << part1() << '\n';
  std::cout << "part2: " << part2() << '\n';

  return 0;
}
