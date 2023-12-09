#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

long next(std::vector<long> v)
{
  std::vector<long> diffs;
  for (int i = 1; i < v.size(); ++i)
    diffs.push_back(v[i] - v[i - 1]);

  for (auto d : diffs)
    if (d != 0)
      return v[v.size() - 1] + next(diffs);
  return v[v.size() - 1];
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;
  long total1 = 0;
  long total2 = 0;
  while (std::getline(file, line)) {
    std::vector<long> r;
    while (!line.empty()) {
      size_t length;
      r.push_back(std::stol(line, &length));
      line = line.substr(length);
    }
    total1 += next(r);
    std::reverse(r.begin(), r.end());
    total2 += next(r);
  }

  std::cout << "part1: " << total1 << '\n';
  std::cout << "part2: " << total2 << '\n';
  return 0;
}
