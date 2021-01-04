#include <sstream>
#include <vector>

#include "test_runner.h"

void PrintVectorPart(std::ostream &dst, const std::vector<int> &);

struct TestCase {
  std::string name{};
  std::vector<int> numbers{};
  std::string expected{};
};

std::vector<TestCase> test_cases = {
    {
        "simple",
        {6, 1, 8, -5, 4},
        "8 1 6",
    },
    {
        "nothing",
        {-6, 1, 8, -5, 4},
        "",
    },
    {
        "reverse",
        {6, 1, 8, 5, 4},
        "4 5 8 1 6",
    },
};

void RunTest(const TestCase &tc) {
  std::stringstream ss;
  PrintVectorPart(ss, tc.numbers);
  AssertEqual(ss.str(), tc.expected);
}

int main() {
  TestRunner runner;
  for (const auto &tc : test_cases) {
    runner.RunTest(RunTest, tc, tc.name);
  }

  return 0;
}
