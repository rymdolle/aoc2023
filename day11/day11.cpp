#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char *argv[])
{
  std::ifstream file("example.txt");
  std::string line;
  std::vector<std::string> map;
  std::vector<int> empty_row;
  std::vector<int> empty_col;
  std::vector<std::pair<int,int>> galaxies;
  for (int row{0}; std::getline(file, line); ++row) {
    map.push_back(line);
    bool empty = true;
    for (int col{0}; col < line.length(); ++col)
      if (line[col] != '.')
        empty = false;
    if (empty) {
      empty_row.push_back(row);
      map.push_back(std::string(line.length(), '.'));
    }
  }

  for (int col{0}; col < map[0].length(); ++col) {
    bool empty = true;
    int row{0};
    for (row = 0; row < map.size(); ++row) {
      if (map[row][col] != '.') {
        galaxies.push_back({col,row});
        empty = false;
      }
    }

    if (empty) {
      for (row = 0; row < map.size(); ++row) {
        empty_col.push_back(col);
        map[row].insert(col, ".");
      }

      ++col;
    }
  }

  std::vector<std::pair<std::pair<int,int>, std::pair<int,int>>> pairs;
  std::cout << galaxies.size() << '\n';
  for (int i{0}; i < galaxies.size(); ++i) {
    for (int j{i+1}; j < galaxies.size(); ++j) {
      pairs.push_back({galaxies[i], galaxies[j]});
    }
  }

  std::cout << pairs.size() << '\n';
  int total = 0;
  for (auto [p1,p2] : pairs) {
    int dx = p2.first - p1.first;
    int dy = p2.second - p1.second;
    std::cout <<  std::setw(2) << dx + dy  << ' '
              <<  std::setw(2) << dx << ' ' << std::setw(2) << dy << ' '
              <<  std::setw(2) << p1.first << ','
              <<  std::setw(2) << p1.second << ' '
              <<  std::setw(2) << p2.first << ','
              <<  std::setw(2) << p2.second << '\n';

    total += std::abs(dx) + std::abs(dy);
  }

  for (auto row : map) {
    std::cout << row << '\n';
  }

  std::cout << "part1: " << total << '\n';

  return 0;
}
