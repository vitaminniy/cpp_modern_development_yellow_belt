#include "split.cpp"
#include "test_runner.h"

void TestSplit() {
  const auto result = SplitIntoWords("C Cpp Java Python");
  AssertEqual(result, std::vector<std::string>{"C", "Cpp", "Java", "Python"});
}

int main() {
  TestRunner runner;
  runner.RunTest(TestSplit, "split");
  return 0;
}
