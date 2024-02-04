#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

struct part {
  int x;
  int m;
  int a;
  int s;
};

std::string apply_rules(std::string rules, part p) {
  auto npos = rules.find(",");
  if (npos == std::string::npos)
    return rules;

  int number;
  switch (rules[0]) {
  case 'x':
    number = p.x;
    break;
  case 'm':
    number = p.m;
    break;
  case 'a':
    number = p.a;
    break;
  case 's':
    number = p.s;
    break;
  }

  size_t end;
  int cmp = std::stoi(rules.substr(2), &end);
  if (rules[1] == '>' && not (number > cmp)) {
    return apply_rules(rules.substr(npos + 1), p);
  } else if (rules[1] == '<' && not (number < cmp)) {
    return apply_rules(rules.substr(npos + 1), p);
  }

  return rules.substr(end+3, npos - (end + 3));
}

int main(int argc, char *argv[])
{
  std::filesystem::path filename("input.txt");
  if (argc > 1)
    filename = argv[1];
  std::ifstream file(filename);
  std::string line;
  std::map<std::string, std::string> workflows;
  while (std::getline(file, line) && !line.empty()) {
    std::stringstream ss(line);
    std::string name;
    std::getline(ss, name, '{');
    std::string rules;
    std::getline(ss, rules, '}');
    workflows[name] = rules;
  }

  int accepted = 0;
  while (std::getline(file, line)) {
    int x = std::stoi(line.substr(line.find("x=")+2));
    int m = std::stoi(line.substr(line.find("m=")+2));
    int a = std::stoi(line.substr(line.find("a=")+2));
    int s = std::stoi(line.substr(line.find("s=")+2));
    std::string rule = "in";
    while (rule != "A" && rule != "R")
      rule = apply_rules(workflows[rule], part{x,m,a,s});

    if (rule == "A")
      accepted += x + m + a + s;
  }

  std::cout << "part1: " << accepted << '\n';
  return 0;
}
