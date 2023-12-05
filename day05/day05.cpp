#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <tuple>
#include <vector>

typedef std::vector<std::tuple<long,long,long>> type_t;

long find(long seed, std::vector<type_t> &types) {
  for (auto type : types) {
    for (auto [dst, src, range] : type) {
      if (seed >= src && seed < src + range) {
        seed = dst + (seed - src);
        break;
      }
    }
  }
  return seed;
}

int main(int argc, char *argv[])
{
  std::ifstream file("input.txt");
  std::string line;
  std::vector<long> seeds;
  std::vector<type_t> types;

  std::getline(file, line);
  line = line.substr(6);
  for (int i = 0; line.length() > 0; ++i) {
    size_t len;
    seeds.push_back(std::stol(line, &len));
    line = line.substr(len);
  }

  while (std::getline(file, line)) {
    if (line.empty()) {
      std::getline(file, line);
      types.push_back(type_t());
      continue;
    }

    size_t len;
    size_t offset = 0;
    long dst = std::stol(line.substr(offset), &len);
    offset += len;
    long src = std::stol(line.substr(offset), &len);
    offset += len;
    long range = std::stol(line.substr(offset), &len);
    types[types.size()-1].push_back({dst, src, range});
  }

  std::vector<long> mapped;
  std::vector<long> mapped_range;
  for (int i = 0; i < seeds.size(); ++i) {
    long seed = seeds[i];
    if (i % 2 == 0) {
      long seed_range = seeds[i+1];
      long min = seed;
      for (int j = 0; j < seed_range; ++j) {
        min = std::min(min, find(seed + j, types));
      }
      mapped_range.push_back(min);
    }
    seed = find(seed, types);
    mapped.push_back(seed);
  }

  long lowest = mapped[0];
  for (auto s : mapped) {
    if (s < lowest)
      lowest = s;
  }

  long lowest_range = mapped_range[0];
  for (auto s : mapped_range) {
    if (s < lowest_range)
      lowest_range = s;
  }

  std::cout << "part1: " << lowest << '\n';
  std::cout << "part2: " << lowest_range << '\n';
  return 0;
}
