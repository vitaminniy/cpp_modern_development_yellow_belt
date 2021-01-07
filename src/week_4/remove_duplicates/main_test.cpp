#include <functional>
#include <string>
#include <vector>

#include "remove.cpp"
#include "test_runner.h"

template <typename T>
std::function<void()> TestRemoveDuplicates(std::vector<T> &&target,
                                           std::vector<T> &&expected) {
  return [&target, expected]() -> void {
    RemoveDuplicates(target);
    AssertEqual(target, expected);
  };
}

int main() {
  TestRunner runner;
  runner.RunTest(TestRemoveDuplicates(std::vector<int>{6, 4, 7, 6, 4, 4, 0, 1},
                                      std::vector<int>{0, 1, 4, 6, 7}),
                 "integers");
  runner.RunTest(TestRemoveDuplicates(
                     std::vector<std::string>{"C", "C++", "C++", "C", "C++"},
                     std::vector<std::string>{"C", "C++"}),
                 "strings");
  return 0;
}
