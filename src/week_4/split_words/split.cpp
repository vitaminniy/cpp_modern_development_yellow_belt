#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> SplitIntoWords(const std::string &s) {
  std::vector<std::string> result;

  auto begin = s.cbegin();
  while (true) {
    auto it = std::find(begin, s.cend(), ' ');
    result.push_back(std::string(begin, it));
    if (it == s.cend()) {
      break;
    }

    begin = ++it;
  }

  return result;
}
