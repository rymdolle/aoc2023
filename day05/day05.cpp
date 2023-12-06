#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <tuple>
#include <vector>
#include <ranges>

typedef std::vector<std::tuple<long, long, long>> type_t;

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

long rfind(long min, std::map<long, long> seeds, std::vector<type_t> &types) {
  for (long location = 0; location < min; ++location) {
    long seed = location;
    for (auto type : std::views::reverse(types)) {
      for (auto [src, dst, range] : type) {
        if (seed >= src && seed < src + range) {
          seed = dst + (seed - src);
          break;
        }
      }
    }
    for (auto [start, end] : seeds) {
      if (seed >= start && seed < end)
        return location;
    }
  }
  return min;
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

  std::vector<long> locations;
  for (auto seed : seeds) {
    long location = find(seed, types);
    locations.push_back(location);
  }
  long closest = *std::min_element(locations.begin(), locations.end());

  std::map<long,long> seed_range;
  for (int i = 0; i < seeds.size(); i += 2) {
      long start = seeds[i];
      long range = seeds[i+1];
      seed_range[start] = start + range;
  }

  std::cout << "part1: " << closest << '\n';
  std::cout << "part2: " << rfind(closest, seed_range, types) << '\n';
  return 0;
}
