#include <algorithm>
#include <string>
#include <utility>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt begin, RandomIt end,
                                             const std::string &prefix) {
  return std::equal_range(
      begin, end, prefix,
      [&prefix](const std::string &a, const std::string &b) {
        return a.compare(0, prefix.length(), b.substr(0, prefix.length())) < 0;
      });
}

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(RandomIt begin, RandomIt end,
                                             char prefix) {
  return FindStartsWith(begin, end, std::string{prefix});
}
