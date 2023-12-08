#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string instructions;
  std::getline(file, instructions);

  std::string line;
  std::getline(file, line); // empty

  std::map<std::string, std::pair<std::string, std::string>> locations;
  while (std::getline(file, line)) {
    auto key = line.substr(0, 3);
    auto l = line.substr(7, 3);
    auto r = line.substr(12, 3);
    locations[key] = {l, r};
  }

  long steps1{0};
  std::string position = "AAA";
  std::string target = "ZZZ";
  while (position != target) {
    if (instructions[steps1 % instructions.size()] == 'L')
      position = locations[position].first;
    else
      position = locations[position].second;

    ++steps1;
  }


  long steps2{1};
  std::vector<std::string> enda;
  std::vector<std::string> endz;
  for (auto [k,v] : locations) {
    if (k[2] == 'A')
      enda.push_back(k);
    if (k[2] == 'Z')
      endz.push_back(k);
  }

  for (auto position : enda) {
    long steps{0};
    bool done = false;
    while (!done) {
      for (char dir : instructions) {
        if (dir == 'L')
          position = locations[position].first;
        else
          position = locations[position].second;

        ++steps;
        auto it = std::find(endz.begin(), endz.end(), position);
        if (it != endz.end()) {
          done = true;
          break;
        }
      }
    }

    steps /= instructions.size();
    steps2 *= steps;
  }

  steps2 *= instructions.size();

  std::cout << "part1: " << steps1 << '\n';
  std::cout << "part2: " << steps2 << '\n';
  return 0;
}
