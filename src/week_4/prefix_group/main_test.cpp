#include <string>
#include <vector>

#include "prefix.cpp"
#include "test_runner.h"

void TestCharPrefix() {
  {
    const std::vector<std::string> sorted_strings = {"moscow", "murmansk",
                                                     "vologda"};
    const auto p =
        FindStartsWith(sorted_strings.begin(), sorted_strings.end(), 'm');

    std::vector<std::string> result;
    result.reserve(2);
    for (auto it = p.first; it != p.second; ++it) {
      result.push_back(*it);
    }

    AssertEqual(result, std::vector<std::string>{"moscow", "murmansk"},
                "m results");
  }
  {
    const std::vector<std::string> sorted_strings = {"moscow", "murmansk",
                                                     "vologda"};
    const auto p =
        FindStartsWith(sorted_strings.begin(), sorted_strings.end(), 'p');
    AssertEqual(p.first - sorted_strings.begin(), 2, "p first");
    AssertEqual(p.second - sorted_strings.begin(), 2, "p second");
  }
  {
    const std::vector<std::string> sorted_strings = {"moscow", "murmansk",
                                                     "vologda"};
    const auto p =
        FindStartsWith(sorted_strings.begin(), sorted_strings.end(), 'z');
    AssertEqual(p.first - sorted_strings.begin(), 3, "z first");
    AssertEqual(p.second - sorted_strings.begin(), 3, "z second");
  }
}

void TestStringPrefix() {
  const std::vector<std::string> sorted_strings = {"moscow", "motovilikha",
                                                   "murmansk"};

  {
    const auto mo_result =
        FindStartsWith(sorted_strings.begin(), sorted_strings.end(), "mo");

    std::vector<std::string> result;
    result.reserve(2);
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
      result.push_back(*it);
    }

    AssertEqual(result, std::vector<std::string>{"moscow", "motovilikha"},
                "mo results");
  }

  {
    const auto mt_result =
        FindStartsWith(sorted_strings.begin(), sorted_strings.end(), "mt");
    AssertEqual(mt_result.first - sorted_strings.begin(), 2, "mt first");
    AssertEqual(mt_result.second - sorted_strings.begin(), 2, "mt second");
  }

  {
    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");

    AssertEqual(na_result.first - sorted_strings.begin(), 3, "na first");
    AssertEqual(na_result.second - sorted_strings.begin(), 3, "na second");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestCharPrefix, "TestCharPrefix");
  runner.RunTest(TestStringPrefix, "TestStringPrefix");

  return 0;
}
