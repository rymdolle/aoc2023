#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> map;
  std::map<int, bool> empty_row;
  std::map<int, bool> empty_col;
  std::vector<std::pair<int,int>> galaxies;

  // Read rows and find empty
  for (int row{0}; std::getline(file, line); ++row) {
    map.push_back(line);
    bool empty = true;
    for (int col{0}; col < line.length(); ++col)
      if (line[col] != '.')
        empty = false;

    if (empty)
      empty_row[row] = true;
  }

  // Find empty cols and galaxies
  for (int col{0}; col < map[0].length(); ++col) {
    bool empty = true;
    for (int row{0}; row < map.size(); ++row) {
      if (map[row][col] != '.') {
        galaxies.push_back({col,row});
        empty = false;
      }
    }

    if (empty)
      empty_col[col] = true;
  }

  // Construct galaxy pairs
  std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> pairs;
  for (int i{0}; i < galaxies.size(); ++i)
    for (int j{i+1}; j < galaxies.size(); ++j)
      pairs.push_back({galaxies[i], galaxies[j]});

  long total1 = 0;
  long total2 = 0;
  for (auto [p1,p2] : pairs) {
    // Find the pair distance
    int dx = std::abs(p2.first - p1.first);
    int dy = std::abs(p2.second - p1.second);

    // Find empty cols
    int ec = 0;
    for (int i = std::min(p1.first, p2.first);
         i < std::max(p1.first, p2.first); ++i) {
      if (empty_col.count(i) > 0)
        ++ec;
    }

    // Find empty rows
    int er = 0;
    for (int i = std::min(p1.second, p2.second);
         i < std::max(p1.second, p2.second); ++i) {
      if (empty_row.count(i) > 0)
        ++er;
    }

    // Sum distance and add an extra row and col for empty space
    total1 += dx + ec + dy + er;

    // Sum distance as in part 1 but multiply empty space by a million
    total2 += dx + ec * (1e6 - 1) + dy + er * (1e6 - 1);
  }

  std::cout << "part1: " << total1 << '\n';
  std::cout << "part2: " << total2 << '\n';

  return 0;
}
