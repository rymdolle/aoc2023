#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void tilt(std::vector<std::string>& disc)
{
  bool moved = true;
  while (moved) {
    moved = false;
    for (int y = 1; y < disc.size(); ++y) {
      for (int x = 0; x < disc[y].length(); ++x) {
        if (disc[y][x] == 'O' && disc[y-1][x] == '.') {
          disc[y][x] = '.';
          disc[y-1][x] = 'O';
          moved = true;
        }
      }
    }
  }
}

int load(std::vector<std::string> disc)
{
  int load = 0;
  for (int y = 0; y < disc.size(); ++y) {
    for (int x = 0; x < disc[y].size(); ++x) {
      if (disc[y][x] == 'O') {
        load += disc.size() - y;
      }
    }
  }
  return load;
}

std::vector<std::string> rotr(std::vector<std::string> disc) {
  std::vector<std::string> tmp(disc[0].length());
  for (int row{0}; row < disc.size(); ++row)
    for (int col{0}; col < disc[row].length(); ++col)
      tmp[col].push_back(disc[row][col]);

  for (auto& row : tmp)
    std::reverse(row.begin(), row.end());
  return tmp;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::string line;
  std::vector<std::string> disc;
  while (std::getline(file, line))
    disc.push_back(line);

  auto disc1 = disc;
  tilt(disc1);
  std::cout << "part1: " << load(disc1) << '\n';


  auto disc2 = disc;
  for (int i = 0; i < 1000; ++i) {
    for (int j = 0; j < 4; ++j) {
      tilt(disc2);
      disc2 = rotr(disc2);
    }
  }

  std::cout << "part2: " << load(disc2) << '\n';
  return 0;
}
