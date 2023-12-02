#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

std::vector<std::string>
get_sets(std::string line, std::string delim)
{
  std::string::size_type pos = 0;
  std::vector<std::string> set;
  for (;;) {
    auto sub = line.find(delim, pos);
    set.push_back(line.substr(pos, sub == std::string::npos ? sub : sub - pos));
    if (sub == std::string::npos)
      break;
    pos = sub + delim.size();
  }
  return set;
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");

  int total_games = 0;
  int total_part1 = 0;
  int total_part2 = 0;
  std::set<int> impossible;
  for (std::string line; std::getline(file, line);) {
    int id = std::stoi(line.substr(5));
    std::map<std::string, int> minimum;
    for (auto set : get_sets(line.substr(line.find(":")+1), ";")) {
      std::map<std::string, int> colors;
      for (auto cube : get_sets(set, ",")) {
        std::size_t pos;
        int count = std::stoi(cube, &pos, 10);
        std::string color = cube.substr(pos+1);
        colors[color] += count;
        minimum[color] = std::max(count, minimum[color]);
      }
      if (colors["red"] > 12 || colors["green"] > 13 || colors["blue"] > 14) {
        impossible.insert(id);
      }
    }
    total_part2 += minimum["red"] * minimum["green"] * minimum["blue"];

    ++total_games;
  }

  for (int game = 1; game <= total_games; ++game)
    if (impossible.count(game) == 0)
      total_part1 += game;

  std::cout << "part1: " << total_part1 << '\n';
  std::cout << "part2: " << total_part2 << '\n';

  return 0;
}
