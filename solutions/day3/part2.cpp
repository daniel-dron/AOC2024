#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int parse_number(const std::string &str, size_t &pos) {
  int num = 0;
  while (pos < str.length() && std::isdigit(str[pos])) {
    num = num * 10 + (str[pos] - '0');
    pos++;
  }
  return num;
}

bool match_sequence(const std::string &content, size_t i,
                    const std::string &pattern) {
  if (i + pattern.length() > content.length())
    return false;
  return content.substr(i, pattern.length()) == pattern;
}

int find_mul(const std::string &content, size_t &i) {
  if (match_sequence(content, i, "mul(")) {

    i += 4;
    int first = parse_number(content, i);

    if (i < content.length() && content[i] == ',') {
      i++;
      int second = parse_number(content, i);

      if (i < content.length() && content[i] == ')') {
        return first * second;
      }
    }
  }

  return 0;
}

int main() {
  std::ifstream file("data.txt");
  std::string content{std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>()};

  int sum = 0;
  bool enabled = true;
  for (size_t i = 0; i < content.length(); i++) {
    if (enabled) {
      sum += find_mul(content, i);
    }

    if (enabled && match_sequence(content, i, "don't()")) {
      enabled = false;
      i += 5;
    } else if (!enabled && match_sequence(content, i, "do()")) {
      enabled = true;
      i += 3;
    }
  }

  std::printf("sum: %d", sum);
}
