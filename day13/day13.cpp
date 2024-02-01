#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <vector>

typedef std::vector<std::string> Mirror;

Mirror rotr(Mirror mirror) {
  Mirror tmp;
  for (int row{0}; row < mirror.size(); ++row) {
    for (int col{0}; col < mirror[row].length(); ++col) {
      if (tmp.size() <= col) {
        tmp.push_back("");
      }
      tmp[col].push_back(mirror[row][col]);
    }
  }

  for (auto& row : tmp) {
    std::reverse(row.begin(), row.end());
  }
  return tmp;
}

Mirror flip(Mirror mirror) {
  Mirror tmp;
  while (tmp.size() < mirror.size()) {
    tmp.push_back(mirror[mirror.size() - tmp.size() - 1]);
  }
  return tmp;
}

void print_mirror(Mirror m)
{
  for (auto& l : m) {
    std::cout << l << '\n';
  }
  std::cout << '\n';
}

int reflection(Mirror mirror)
{
  int n = 0;
  for (int rot = 0; rot < 4; ++rot) {
    print_mirror(mirror);
    int end = mirror.size() - 1;
    for (int i = 0; i < mirror.size(); ++i) {
      if (mirror[i] == mirror[end] && i != end) {
        std::cout << i << ' ' << end << '\n';
        if ((end - i) % 2 != 1) {
          std::cout << "contine\n";
          continue;
        }
        int j = 0;
        bool match = true;
        for (; i + j < end - j; ++j) {
          if (mirror[i + j] != mirror[end - j]) {
            match = false;
            break;
          }
        }
        if (match) {
          n = i + j;
          std::cout << "match " << n << ' ' << rot << "\n";
          goto label;
        }
      }
    }
  label:
    if (n == 0) {
      std::cout << "rotate\n";
      mirror = rotr(mirror);
    } else {
      if (rot == 0)
        return n * 100;
      else if (rot == 1)
        return n;
      else if (rot == 2)
        return (mirror.size() - n) * 100;
      else if (rot == 3)
        return (mirror.size() - n);
    }
  }
  return n;
}

int main(int argc, char *argv[])
{
  std::string filename = "input.txt";
  if (argc > 1) filename = argv[1];
  std::ifstream file(filename);
  std::string line;

  std::vector<Mirror> mirrors;
  Mirror tmp;
  while (std::getline(file, line)) {
    if (line.empty()){
      mirrors.push_back(tmp);
      tmp.clear();
      continue;
    }
    tmp.push_back(line);
  }

  if (tmp.size() > 0)
    mirrors.push_back(tmp);

  int total{0};
  for (auto mirror : mirrors) {
    int n = reflection(mirror);
    // if (n == 0)
    //   return 1;
    std::cout << "n: " << n
              << '\n'
              << '\n'
              << '\n'
              << '\n';
    //print_mirror(mirror);
    total += n;
  }
  std::cout << '\n';

  std::cout << "part1: " << total << '\n';

  return 0;
}
