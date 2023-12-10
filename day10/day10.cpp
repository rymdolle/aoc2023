#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<const char*> glyphs = {
  "\u00A0", //  1  space
  "\u2554", //  2  ╔
  "\u2557", //  3  ╗
  "\u255A", //  4  ╚
  "\u255D", //  5  ╝
  "\u2550", //  6  ═
  "\u2551", //  7  ║
  "\u2560", //  8  ╠
  "\u2563", //  9  ╣
  "\u2566", // 10  ╦
  "\u2569", // 11  ╩
  "\u256C", // 12  ╬
};

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

  auto pos = start;
  --pos.second;
  direction dir = direction::north;
  int steps = 1;
  while (start != pos) {
    char c = map[pos.second][pos.first];
    std::cout << c << ' ' << pos.first << ',' << pos.second << '\n';
    switch (c) {

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
    ++steps;
  }

  char c = map[pos.second][pos.first];
  std::cout << c << ' ' << steps / 2 << '\n';

  return 0;
}
