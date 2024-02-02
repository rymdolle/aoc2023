#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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
  std::vector<std::pair<int,int>> holes;
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].length(); ++x) {
      bool member = false;
      for (auto [xx, yy] : pipes) {
        if (xx == x && yy == y) {
          member = true;
          break;
        }
      }

      if (!member) {
        holes.push_back({x,y});
      }
    }
  }

  int total = 0;
  std::vector<std::pair<int,int>> inside;
  for (auto [x,y] : holes) {
    std::vector<std::pair<int,int>> row;
    std::copy_if(pipes.begin(), pipes.end(), std::back_inserter(row),
                 [&y](std::pair<int,int> p) {return p.second == y;});
    int count = 0;
    for (int i = 0; i < row.size(); ++i) {
      if (row[i].first >= x)
        continue;
      if (map[row[i].second][row[i].first] == '|' ||
          map[row[i].second][row[i].first] == 'L' ||
          map[row[i].second][row[i].first] == 'J') {
        ++count;
      }
    }
    if (count % 2 == 1) {
      inside.push_back({x,y});
      ++total;
    }
  }

  std::vector<std::string> v(map.size(), std::string(map[0].length(), ' '));
  for (auto [x,y] : holes) {
    v[y].erase(x, 1);
    v[y].insert(x, "O");
  }
  for (auto [x,y] : inside) {
    v[y].erase(x, 1);
    v[y].insert(x, "I");

  }
  v[start.second][start.first] = 'S';
  for (int i = 0; i < map.size(); ++i) {
    std::vector<std::pair<int,int>> n;
    std::copy_if(pipes.begin(), pipes.end(), std::back_inserter(n),
                 [&i](std::pair<int,int> b) {return b.second == i;});
    std::sort(n.begin(), n.end(), [](auto a, auto b) {return a.first>b.first;});
    for (auto [x,y] : n) {
      if (v[y][x] == 'S')
        continue;
      v[y].erase(x, 1);
      if (map[y][x] == '|')
        v[y].insert(x, glyphs[6]);
      else if (map[y][x] == '-')
        v[y].insert(x, glyphs[5]);
      else if (map[y][x] == 'F')
        v[y].insert(x, glyphs[1]);
      else if (map[y][x] == '7')
        v[y].insert(x, glyphs[2]);
      else if (map[y][x] == 'L')
        v[y].insert(x, glyphs[3]);
      else if (map[y][x] == 'J')
        v[y].insert(x, glyphs[4]);
      else
        v[y].insert(x, glyphs[0]);
    }
  }

  for (auto row : v)
    std::cout << row << '\n';

  std::cout << "part1: " << pipes.size() / 2 << '\n';
  std::cout << "part2: " << total << '\n';

  return 0;
}
