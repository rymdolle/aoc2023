#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

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

  int load = 0;
  for (int y = 0; y < disc.size(); ++y) {
    for (int x = 0; x < disc[y].size(); ++x) {
      if (disc[y][x] == 'O') {
        load += disc.size() - y;
      }
    }
  }

  std::cout << "part1: " << load << '\n';

  return 0;
}
