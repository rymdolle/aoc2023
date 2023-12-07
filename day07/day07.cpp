#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <ranges>
#include <vector>
#include <algorithm>

struct Hand
{
public:
  std::string cards;
  long bet;

  Hand replace_joker() {
    auto c = counts();
    char highest = c[0].second;
    for (int i = 1; i < c.size() && highest == 'J'; ++i)
      highest = c[i].second;
    // Replace all jokers with the card with highest count
    Hand tmp(cards, bet);
    std::replace(tmp.cards.begin(), tmp.cards.end(), 'J', highest);
    return tmp;
  }

  static bool compare_cards(char a, char b, std::vector<char> &points)
  {
    return
      std::find(points.begin(), points.end(), a)
      >
      std::find(points.begin(), points.end(), b);
  }

  bool compare(Hand b, std::vector<char> &points)
  {
    int ap = replace_joker().points();
    int bp = b.replace_joker().points();
    if (ap == bp) {
      for (int i = 0; i < cards.size() && i < b.cards.size(); ++i) {
        if (cards[i] != b.cards[i])
          return compare_cards(cards[i], b.cards[i], points);
      }
    }
    return ap > bp;
  }

  char highest(std::vector<char> &points)
  {
    char highest = cards[0];
    for (int i = 1; i < cards.size(); ++i) {
      if (compare_cards(highest, cards[i], points))
        highest = cards[i];
    }
    return highest;
  }

  std::vector<std::pair<int, char>> counts()
  {
    std::map<char, int> counts;
    for (auto card : cards)
      ++counts[card];

    std::vector<std::pair<int, char>> max;
    for (auto [k,v] : counts)
      max.push_back({v,k});

    std::sort(max.begin(), max.end(), [](auto a, auto b) {
      return a.first > b.first;
    });

    return max;
  }

  int points()
  {
    // 1 23456 - high card
    // 2 A23A4 - one pair
    // 3 23432 - two pair
    // 4 TTT98 - three of a kind
    // 5 23332 - three of a kind + pair
    // 6 AA8AA - four of a kind
    // 7 AAAAA - five of a kind
    auto max = counts();

    switch (max[0].first) {
    case 5:
      return 7;
    case 4:
      return 6;
    case 3:
      if (max[1].first == 2)
        return 5;
      else
        return 4;
    case 2:
      if (max[1].first == 2)
        return 3;
      else
        return 2;
    case 1:
      return 1;
    }
    return 0;
  }
};

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<Hand> hands;
  while (std::getline(file, line)) {
    auto pos = line.find(" ");
    std::string cards = line.substr(0, pos);
    int bet = std::stoi(line.substr(pos));

    Hand h{cards, bet};
    hands.push_back(h);
  }

  std::vector<char> p1{'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
  std::sort(hands.begin(), hands.end(), [&p1](Hand &a, Hand &b) {
    return a.compare(b, p1);
  });

  long long total1 = 0;
  for (auto [n,h] : hands
         | std::views::reverse
         | std::views::enumerate) {
    total1 += (n+1) * h.bet;
  }

  std::vector<char> p2{'J','2','3','4','5','6','7','8','9','T','Q','K','A'};
  std::sort(hands.begin(), hands.end(), [&p2](Hand &a, Hand &b) {
    return a.compare(b, p2);
  });

  long long total2 = 0;
  for (auto [n,h] : hands
         | std::views::reverse
         | std::views::enumerate) {
    total2 += (n+1) * h.bet;
  }

  std::cout << "part1: " << total1 << '\n';
  std::cout << "part2: " << total2 << '\n';

  return 0;
}
