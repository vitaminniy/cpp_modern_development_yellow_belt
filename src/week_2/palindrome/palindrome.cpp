#include <iostream>
#include <map>
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
    std::stringstream os;
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

bool IsPalindrom(const std::string &str) {
  if (str.empty() || str.size() == 1)
    return true;

  for (size_t i = 0; i < str.size() / 2; i++) {
    const auto end = str.size() - 1 - i;
    if (str.at(i) != str.at(end))
      return false;
  };

  return true;
}

void TestIsPalindrom() {
  Assert(IsPalindrom(""), "empty string is palindrom");
  Assert(IsPalindrom("a"), "one-symbol string is palindrom");

  Assert(IsPalindrom("madam"), "madam is palindrom");
  Assert(IsPalindrom("ma d am"), "ma d am is palindrom");
  Assert(!IsPalindrom("madama"), "madama is not palindrom");
  Assert("adam", "madam first symbol not ignored");
  Assert("mada", "madam last symbol not ignored");

  Assert(IsPalindrom("level"), "level is palindrom");
  Assert(!IsPalindrom("levell"), "levell is not palindrom");
  Assert(!IsPalindrom(" level"), "level spaces not ignored");
  Assert("evel", "level first symbol not ignored");
  Assert("leve", "level last symbol not ignored");

  Assert(!IsPalindrom("aqweewq"), "first symbol not ignored");
  Assert(!IsPalindrom("qweewqa"), "last symbol not ignored");

  Assert(IsPalindrom("AA"), "expected AA to be palindrom");
  Assert(!IsPalindrom("aA"), "palindrom is case-sensitive");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrom");

  return 0;
}
