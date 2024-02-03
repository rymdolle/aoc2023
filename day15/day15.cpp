#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

int hash(std::string text)
{
  unsigned char sum = 0;
  for (auto& c : text) {
    sum += c;
    sum *= 17;
  }
  return sum;
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::string line;

  int total = 0;
  std::map<unsigned char, std::vector<std::pair<std::string, int>>> hashmap;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string seq;
    while (std::getline(ss, seq, ',')) {
      total += hash(seq);
      if (auto npos = seq.find('='); npos != std::string::npos) {
        std::string label = seq.substr(0, npos);
        int focal_length = std::stoi(seq.substr(npos+1));
        int box = hash(label);
        bool found = false;
        for (auto it = hashmap[box].begin(); it != hashmap[box].end(); ++it) {
          if (it->first == label) {
            it->second = focal_length;
            found = true;
            break;
          }
        }

        if (!found) {
          hashmap[box].emplace_back(label, focal_length);
        }
      } else if (auto npos = seq.find('-'); npos != std::string::npos) {
        std::string label = seq.substr(0, npos);
        int box = hash(label);
        for (auto it = hashmap[box].begin(); it != hashmap[box].end(); ++it) {
          if (it->first == label) {
            hashmap[box].erase(it);
            break;
          }
        }
      }
    }
  }

  int fpower = 0;
  for (int box = 0; box < hashmap.size(); ++box) {
    for (int slot = 0; slot < hashmap[box].size(); ++slot) {
      fpower += (box + 1) * (slot + 1) * hashmap[box][slot].second;
    }
  }

  std::cout << "part1: " << total << '\n';
  std::cout << "part2: " << fpower << '\n';

  return 0;
}
