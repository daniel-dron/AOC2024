#include "common.hpp"
#include <algorithm>
#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>


int main() {
  std::ifstream file("day1.txt");
  file.tie(nullptr);
  std::ios::sync_with_stdio(false);

  std::vector<int> left;
  std::vector<int> right;

  std::string line;
  line.reserve(5); // 3...5

  while (std::getline(file, line)) {
    int l, r = {};
    std::string_view sv = line;
    auto pos = sv.find_first_of(" ");
    std::from_chars(sv.data(), sv.data() + pos, l);
    auto pos2 = sv.find_first_not_of(" ", pos);
    std::from_chars(sv.data() + pos2, sv.data() + sv.size(), r);

    left.emplace_back(l);
    right.emplace_back(r);
  }

  // 1. order both vectors
  // 2. for the first number on the L, find how many times its in R
  // 3. reuse value from 2. for each equal number

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  int sum = {};

  int last_l = 0;
  int last_s = 0;
  for (auto l : left) {
    if (l == last_l) {
        sum += last_s;
    }

    last_l = l;
  
    int count = std::ranges::count(right, l);
    last_s = l * count;

    sum += last_s;
  }

  std::printf("answer: %d\n", sum);
}