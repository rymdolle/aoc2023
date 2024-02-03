#include <filesystem>
#include <fstream>
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
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string seq;
    while (std::getline(ss, seq, ','))
      total += hash(seq);
  }

  std::cout << "part1: " << total << '\n';

  return 0;
}
