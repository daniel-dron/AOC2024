#include "common.hpp"
#include <algorithm>
#include <charconv>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include <numeric>

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

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  int distance = {};
  for(const auto [l, r] : std::views::zip(left, right)) {
    distance += std::abs(l - r);
  }

  std::printf("answer: %d\n", distance);
}