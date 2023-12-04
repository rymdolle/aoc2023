#include <fstream>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <ranges>

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");

  std::map<int, int> cards;
  for (std::string line; std::getline(file, line);) {
    size_t len;
    int card = std::stoi(line.substr(4), &len);
    auto pos = line.find("|");
    std::string my_numbers = line.substr(pos + 1);
    std::string winning_str = line.substr(5+len, pos-(5+len+1));

    std::set<int> winning;
    for (int i = 0; i < winning_str.length(); i += len) {
      int number = std::stoi(winning_str.substr(i), &len);
      winning.insert(number);
    }

    cards[card] = 0;
    for (int i = 0; i < my_numbers.length(); i += len) {
      int number = std::stoi(my_numbers.substr(i), &len);
      if (winning.find(number) != winning.end())
        ++cards[card];
    }
  }

  int total_points = 0;
  int total_cards = 0;
  std::map<int, int> copy;
  for (auto [key, value] : cards) {
    if (value > 0)
      total_points += 1 << (value - 1);
    copy[key] += 1;
    for (int i = 0; i < value; ++i)
      copy[key+i+1] += copy[key];
    total_cards += copy[key];
  }

  std::cout << "part1: " << total_points << '\n';
  std::cout << "part2: " << total_cards  << '\n';
  return 0;
}
