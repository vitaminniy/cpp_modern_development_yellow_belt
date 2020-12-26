#pragma once

#include <string>

namespace tests {

template <class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint);

inline void Assert(bool b, const std::string &hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  TestRunner() = default;
  ~TestRunner();

  template <class TestFunc>
  void RunTest(TestFunc func, const std::string &test_name);

private:
  int fail_count = 0;
};

} // namespace tests
