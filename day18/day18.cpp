#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void flood_fill(int x, int y, std::vector<std::string>& trench)
{
  if (x < 0 || x >= trench[0].size() || y < 0 || y >= trench.size())
    return;
  if (trench[y][x] == '#')
    return;
  if (trench[y][x] == '.') {
    trench[y][x] = 'O';
    flood_fill(x+1, y, trench);
    flood_fill(x-1, y, trench);
    flood_fill(x, y+1, trench);
    flood_fill(x, y-1, trench);
  }
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::string line;
  std::vector<std::pair<int,int>> plan;
  int x = 0;
  int y = 0;
  int wmax = 0;
  int wmin = 0;
  int hmax = 0;
  int hmin = 0;
  while (std::getline(file, line)) {
    char dir = line[0];
    size_t end;
    int len = std::stoi(line.substr(1), &end, 10);
    int hex = std::stoi(line.substr(end+4), &end, 16);
    switch (dir) {
    case 'R':
      for (int i = 0; i < len; ++i) {
        plan.push_back({x,y});
        ++x;
      }
      break;
    case 'L':
      for (int i = 0; i < len; ++i) {
        plan.push_back({x,y});
        --x;
      }
      break;
    case 'U':
      for (int i = 0; i < len; ++i) {
        plan.push_back({x,y});
        --y;
      }
      break;
    case 'D':
      for (int i = 0; i < len; ++i) {
        plan.push_back({x,y});
        ++y;
      }
      break;
    }
    wmax = std::max(wmax, x);
    wmin = std::min(wmin, x);
    hmax = std::max(hmax, y);
    hmin = std::min(hmin, y);
  }

  int w = wmax - wmin;
  int h = hmax - hmin;
  std::cout << w << ' ' << h << '\n';
  // Add border to flood fill from the edge
  std::vector<std::string> trench(h+3, std::string(w+3, '.'));
  for (auto& [tx,ty] : plan) {
    trench[ty-hmin+1][tx-wmin+1] = '#';
  }

  // Fill empty space
  flood_fill(0, 0, trench);

  // Count lava trench space
  int size = 0;
  for (const auto& t : trench) {
    for (const auto& c : t) {
      if (c == '#' || c == '.')
        ++size;
    }
  }

  std::cout << "part1: " << size << '\n';

  return 0;
}
