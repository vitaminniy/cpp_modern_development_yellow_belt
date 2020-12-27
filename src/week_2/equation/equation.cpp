#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &s) {
  os << "{";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
  os << "{";
  bool first = true;
  for (const auto &x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
  os << "{";
  bool first = true;
  for (const auto &kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint = {}) {
  if (t != u) {
    std::ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw std::runtime_error(os.str());
  }
}

void Assert(bool b, const std::string &hint) { AssertEqual(b, true, hint); }

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const std::string &test_name) {
    try {
      func();
      std::cerr << test_name << " OK" << std::endl;
    } catch (std::exception &e) {
      ++fail_count;
      std::cerr << test_name << " fail: " << e.what() << std::endl;
    } catch (...) {
      ++fail_count;
      std::cerr << "Unknown exception caught" << std::endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  if (a == 0 && b == 0)
    return 0;
  if (a == 0)
    return 1;
  const double d = (b * b) - (4 * a * c);
  if (d < 0)
    return 0;
  if (d == 0)
    return 1;
  return 2;
}

void TestLinear() {
  const auto roots = GetDistinctRealRootCount(0, 2, 4);
  AssertEqual(roots, 1, "2x + 4 = 0");
}

void TestTwoRoots() {
  const auto roots = GetDistinctRealRootCount(1, 1, -4);
  AssertEqual(roots, 2, "positive discriminant: x^2 - x - 4 = 0");
}

void TestSingleRoot() {
  const auto roots = GetDistinctRealRootCount(1, -2, 1);
  AssertEqual(roots, 1, "zero discriminant: x^2 - 2x + 1 = 0");
}

void TestNoRoots() {
  {
    const auto roots = GetDistinctRealRootCount(0, 0, 1);
    AssertEqual(roots, 0, "6 = 0"); // WTF
  }
  {
    const auto roots = GetDistinctRealRootCount(1, 1, 100);
    AssertEqual(roots, 0, "negative discriminant: x^2 + x + 100 = 0");
  }
}

void TestPartialEquation() {
  const auto roots = GetDistinctRealRootCount(2, 0, -18);
  AssertEqual(roots, 2, "2x^2 - 18 = 0");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestLinear, "TestLinear");
  runner.RunTest(TestTwoRoots, "TestTwoRoots");
  runner.RunTest(TestSingleRoot, "TestSingleRoot");
  runner.RunTest(TestNoRoots, "TestNoRoots");
  runner.RunTest(TestPartialEquation, "TestPartialEquation");

  return 0;
}
