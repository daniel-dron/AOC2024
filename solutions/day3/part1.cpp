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

int main() {
  std::ifstream file("data.txt");
  std::string content{std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>()};

  int sum = 0;

  for (size_t i = 0; i < content.length(); i++) {
    if (i + 3 < content.length() && content[i] == 'm' &&
        content[i + 1] == 'u' && content[i + 2] == 'l' &&
        content[i + 3] == '(') {

      i += 4;
      int first = parse_number(content, i);

      if (i < content.length() && content[i] == ',') {
        i++;
        int second = parse_number(content, i);

        if (i < content.length() && content[i] == ')') {
          sum += first * second;
        }
      }
    }
  }

  std::printf("sum: %d", sum);
}
