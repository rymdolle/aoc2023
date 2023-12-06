#include <fstream>
#include <iomanip>
#include <string>
#include <iostream>
#include <thread>
#include <ranges>
#include <vector>

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;

  std::getline(file, line);
  std::vector<long> times;
  for (int i = 5; i < line.length();) {
    size_t len;
    long time = std::stol(line.substr(i), &len);
    times.push_back(time);
    i += len;
  }

  std::getline(file, line);
  std::vector<long> dists;
  for (int i = 9; i < line.length();) {
    size_t len;
    long dist = std::stol(line.substr(i), &len);
    dists.push_back(dist);
    i += len;
  }

  auto wins = [](long t, long d) {
    long total = 0;
    for (int i = 1; i < t; ++i)
      if ((t - i) * i > d)
        ++total;
    return total;
  };
  long total_wins = 1;
  std::string stime;
  std::string sdist;
  for (auto [time, dist] : std::views::zip(times, dists)) {
    stime += std::to_string(time);
    sdist += std::to_string(dist);
    total_wins *= wins(time, dist);
  }

  std::cout << "part1: " << total_wins << '\n';
  std::cout << "part2: " << wins(std::stol(stime), std::stol(sdist)) << '\n';
  return 0;
}
