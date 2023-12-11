#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

enum class direction {
  none,
  north,
  south,
  east,
  west,
};

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<std::string> map;
  std::pair<int,int> start;
  while (std::getline(file, line)) {
    map.push_back(line);
    for (int i = 0; i < line.length(); ++i)
      if (line[i] == 'S')
        start = {i, map.size() - 1};
  }

  std::cout << "start: " << start.first << ' ' << start.second << '\n';
  std::vector<std::pair<int,int>> pipes;
  map[start.second][start.first] = '|';
  auto pos = start;
  pipes.push_back(pos);
  ++pos.second;
  direction dir = direction::south;
  while (start != pos) {
    pipes.push_back(pos);
    switch (map[pos.second][pos.first]) {

    case '7':
      if (dir == direction::east) {
        ++pos.second;
        dir = direction::south;
      } else if (dir == direction::north) {
        --pos.first;
        dir = direction::west;
      } else {
        pos = start;
      }
      break;

    case 'J':
      if (dir == direction::east) {
        --pos.second;
        dir = direction::north;
      } else if (dir == direction::south) {
        --pos.first;
        dir = direction::west;
      } else {
        pos = start;
      }
      break;

    case 'F':
      if (dir == direction::west) {
        ++pos.second;
        dir = direction::south;
      } else if (dir == direction::north) {
        ++pos.first;
        dir = direction::east;
      } else {
        pos = start;
      }
      break;

    case 'L':
      if (dir == direction::west) {
        --pos.second;
        dir = direction::north;
      } else if (dir == direction::south) {
        ++pos.first;
        dir = direction::east;
      } else {
        pos = start;
      }
      break;

    case '|':
      if (dir == direction::north) {
        --pos.second;
      } else if (dir == direction::south) {
        ++pos.second;
      } else {
        pos = start;
      }
      break;

    case '-':
      if (dir == direction::east) {
        ++pos.first;
      } else if (dir == direction::west) {
        --pos.first;
      } else {
        pos = start;
      }
      break;
    case '.':
      pos = start;
      break;
    case 'S':
      break;
    }
  }

  int inside = 0;
  for (int y = 0; y < map.size(); ++y) {
    int count = 0;
    for (int x = 0; x < map[y].length(); ++x) {
      auto it = std::find(pipes.begin(), pipes.end(), std::pair{x,y});
      if (it != pipes.end()) {
        if (map[y][x] == '|' || map[y][x] == 'L' || map[y][x] == 'J') {
          ++count;
        }
      }

      if (it == pipes.end() && count % 2 == 1)
        ++inside;
    }
  }

  std::cout << "part1: " << pipes.size() / 2 << '\n';
  std::cout << "part2: " << inside << '\n';

  return 0;
}
