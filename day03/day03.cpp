#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>

struct number {
  int row;
  int col;
  size_t len;
  int value;
};

struct symbol {
  int row;
  int col;
  char type;
};

bool is_adjacent(symbol s, number n)
{
  if (n.row == s.row || n.row == s.row + 1 || n.row == s.row - 1)
    return s.col >= n.col - 1 && s.col <= n.col + n.len;

  return false;
}

char find_symbol(number n, std::vector<symbol> &symbols)
{
  for (auto s : symbols)
    if (is_adjacent(s, n))
      return s.type;

  return '\0';
}

int find_gear_ratio(symbol s, std::vector<number> &numbers)
{
  std::vector<number> gears;
  for (auto n : numbers)
    if (is_adjacent(s, n))
      gears.push_back(n);

  return gears.size() == 2 ? gears[0].value * gears[1].value : 0;
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::vector<number> numbers;
  std::vector<symbol> symbols;

  std::string line;
  for (int row = 0; std::getline(file, line); ++row) {
    for (int i = 0; i < line.length(); ++i) {
      if (line[i] >= '0' && line[i] <= '9') {
        // found number
        size_t len;
        int n = std::stoi(line.substr(i), &len, 10);
        numbers.push_back(number {
            .row   = row,
            .col   = i,
            .len   = len,
            .value = n,
          });
        i += len - 1;
      } else if (line[i] != '.') {
        // Found symbol
        symbols.push_back(symbol {
            .row  = row,
            .col  = i,
            .type = line[i]
          });
      }
    }
  }

  long total_parts = 0;
  for (auto n : numbers) {
    if (find_symbol(n, symbols) != '\0')
      total_parts += n.value;
  }

  int total_ratio = 0;
  // filter all gears and calculate ratio
  auto gears = [](symbol s) { return s.type == '*'; };
  for (auto s : symbols | std::views::filter(gears)) {
    total_ratio += find_gear_ratio(s, numbers);
  }

  std::cout << "part1: " << total_parts << '\n';
  std::cout << "part2: " << total_ratio << '\n';
  return 0;
}
