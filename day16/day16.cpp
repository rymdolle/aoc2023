#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <vector>

enum class direction {
  north,
  south,
  east,
  west,
};

struct state {
  int x;
  int y;
  enum direction dir;
};

typedef std::vector<std::string> Contraption;

void shine(state s, Contraption& grid, std::map<std::pair<int,int>, int>& tiles)
{
  int x = s.x;
  int y = s.y;
  auto dir = s.dir;
  while (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
    ++tiles[{x,y}];
    if (grid[y][x] == '\\') {
      switch (dir) {
      case direction::east:
        dir = direction::south;
        ++y;
        break;
      case direction::west:
        dir = direction::north;
        --y;
        break;
      case direction::south:
        dir = direction::east;
        ++x;
        break;
      case direction::north:
        dir = direction::west;
        --x;
        break;
      }

    } else if (grid[y][x] == '/') {
      switch (dir) {
      case direction::east:
        dir = direction::north;
        --y;
        break;
      case direction::west:
        dir = direction::south;
        ++y;
        break;
      case direction::south:
        dir = direction::west;
        --x;
        break;
      case direction::north:
        dir = direction::east;
        ++x;
        break;
      }

    } else if (grid[y][x] == '-') {
      switch (dir) {
      case direction::east:
        ++x;
        break;
      case direction::west:
        --x;
        break;
      case direction::south:
      case direction::north:
        if (tiles[{x,y}] == 1) {
          shine({x-1, y, direction::west}, grid, tiles);
          shine({x+1, y, direction::east}, grid, tiles);
        }
        return;
      }

    } else if (grid[y][x] == '|') {
      switch (dir) {
      case direction::east:
      case direction::west:
        if (tiles[{x,y}] == 1) {
          shine({x, y-1, direction::north}, grid, tiles);
          shine({x, y+1, direction::south}, grid, tiles);
        }
        return;
      case direction::south:
        ++y;
        break;
      case direction::north:
        --y;
        break;
      }

    } else if (grid[y][x] == '.') {
      switch (dir) {
      case direction::east:
        ++x;
        break;
      case direction::west:
        --x;
        break;
      case direction::south:
        ++y;
        break;
      case direction::north:
        --y;
        break;
      }
    }
  }
}

size_t energize(state s, Contraption c)
{
  std::map<std::pair<int,int>, int> t;
  shine(s, c, t);
  return t.size();
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::string line;
  Contraption grid;
  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  size_t energized_max = 0;
  for (int start = 0; start < grid.size(); ++start) {
    int startx = grid[0].size() - 1;
    int starty = grid[0].size() - 1;
    size_t max1 = energize({0,      start,  direction::east}, grid);
    size_t max2 = energize({startx, start,  direction::west}, grid);
    size_t max3 = energize({start,  0,      direction::south}, grid);
    size_t max4 = energize({start,  starty, direction::north}, grid);
    energized_max = std::max(energized_max, max1);
    energized_max = std::max(energized_max, max2);
    energized_max = std::max(energized_max, max3);
    energized_max = std::max(energized_max, max4);
  }

  std::cout << "part1: " << energize({0,0,direction::east}, grid) << '\n';
  std::cout << "part2: " << energized_max << '\n';

  return 0;
}
