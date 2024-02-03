#include <filesystem>
#include <fstream>
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

void shine(state s, Contraption& grid, Contraption& tiles)
{
  int x = s.x;
  int y = s.y;
  auto dir = s.dir;
  while (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
    if (grid[y][x] == '\\') {
      tiles[y][x] = '#';
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
      tiles[y][x] = '#';
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
        tiles[y][x] = '#';
        ++x;
        break;
      case direction::west:
        tiles[y][x] = '#';
        --x;
        break;
      case direction::south:
      case direction::north:
        if (tiles[y][x] == '.') {
          tiles[y][x] = '#';
          shine({x-1, y, direction::west}, grid, tiles);
          shine({x+1, y, direction::east}, grid, tiles);
        }
        return;
      }

    } else if (grid[y][x] == '|') {
      switch (dir) {
      case direction::east:
      case direction::west:
        if (tiles[y][x] == '.') {
          tiles[y][x] = '#';
          shine({x, y-1, direction::north}, grid, tiles);
          shine({x, y+1, direction::south}, grid, tiles);
        }
        return;
      case direction::south:
        tiles[y][x] = '#';
        ++y;
        break;
      case direction::north:
        tiles[y][x] = '#';
        --y;
        break;
      }

    } else if (grid[y][x] == '.') {
      tiles[y][x] = '#';
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

  Contraption tiles(grid.size(), std::string(grid[0].size(), '.'));
  shine({0, 0, direction::east}, grid, tiles);

  int energized = 0;
  for (auto& row : tiles) {
    std::cout << row << '\n';
    for (auto& col : row) {
      energized += col == '#';
    }
  }

  std::cout << "part1: " << energized << '\n';

  return 0;
}
