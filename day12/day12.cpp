#include <fstream>
#include <string>
#include <iostream>
#include <vector>

bool is_valid(std::string springs, std::vector<int> amount)
{
  int pos{0};
  std::vector<int> groups;
  for (auto c : springs) {
    if (c == '.') {
      if (pos > 0)
        groups.push_back(pos);
      pos = 0;
    } else if (c == '#') {
      ++pos;
    } else {
      std::cout << "impossible " << c << pos << '\n';
      exit(1);
    }
  }
  if (pos > 0)
    groups.push_back(pos);

  if (groups.size() != amount.size())
    return false;
  for (int i{0}; i < amount.size(); ++i) {
    if (groups[i] != amount[i])
      return false;
  }
  std::cout << springs << '\n';
  return true;
}

int generate(int i, std::string springs, std::vector<int> amount)
{
  if (i == springs.size()) {
    return is_valid(springs, amount) ? 1 : 0;
  }
  if (springs[i] == '?') {
    return
      generate(i+1, springs.replace(i, 1, 1, '#'), amount)
      +
      generate(i+1, springs.replace(i, 1, 1, '.'), amount);
  } else {
    return generate(i+1, springs, amount);
  }
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;

  long total1{0};
  long total2{0};
  while (std::getline(file, line)) {
    std::string springs;
    for (int i{0}; i < line.length(); ++i) {
      if (line[i] == ' ') {
        line = line.substr(i);
        break;
      }

      springs += line[i];
    }

    std::cout << springs << '\n';
    line = line.substr(1);

    std::vector<int> amount;
    for (int i{0}; i < line.length();) {
      size_t length;
      int count = std::stoi(line.substr(i), &length);
      std::cout << count << ' ';
      amount.push_back(count);
      i += length + 1;
    }
    std::cout << '\n';

    total1 += generate(0, springs, amount);
    //total2 += generate(0, springs, amount);
  }

  std::cout << "part1: " << total1 << '\n';
  std::cout << "part2: " << total2 << '\n';

  return 0;
}
