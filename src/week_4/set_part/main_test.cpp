#include <functional>
#include <set>
#include <string>
#include <vector>

#include "set_part.cpp"
#include "test_runner.h"

template <typename T> struct TestCase {
  std::set<T> elements{};
  T border{};
  std::vector<T> expected{};
};

template <typename T> std::function<void()> Run(const TestCase<T> &test_case) {
  return [test_case]() -> void {
    const auto result =
        FindGreaterElements(test_case.elements, test_case.border);
    AssertEqual(result, test_case.expected);
  };
}

int main() {
  TestRunner runner;
  runner.RunTest(Run(TestCase<int>{
                     {1, 5, 7, 8},
                     5,
                     {7, 8},
                 }),
                 "ints");
  runner.RunTest(Run(TestCase<std::string>{
                     {"C++", "C#", "Ada", "C", "Java", "Python"},
                     "C#",
                     {"C++", "Java", "Python"},
                 }),
                 "string");

  return 0;
}
