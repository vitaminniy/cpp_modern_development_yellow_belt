#include <iostream>
#include <map>
#include <numeric>
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

class Rational {
public:
  inline Rational() : numerator_(0), denominator_(1) {}
  Rational(int numerator, int denominator) {
    if (numerator == 0) {
      numerator_ = numerator;
      denominator_ = 1;
      return;
    }

    if (denominator < 0) {
      denominator *= -1;
      numerator *= -1;
    }

    const auto div = std::gcd(numerator, denominator);
    numerator_ = numerator / div;
    denominator_ = denominator / div;
  }

  inline int Numerator() const { return numerator_; };
  inline int Denominator() const { return denominator_; };

private:
  int numerator_;
  int denominator_;
};

void TestDefaultConstructor() {
  Rational r;
  AssertEqual(r.Numerator(), 0, "numerator");
  AssertEqual(r.Denominator(), 1, "denominator");
}

void TestZeroNumerator() {
  Rational r(0, 100);
  AssertEqual(r.Numerator(), 0, "numerator");
  AssertEqual(r.Denominator(), 1, "denominator");
}

void TestPositive() {
  {
    Rational r(2, 3);
    AssertEqual(r.Numerator(), 2, "numerator 2/3");
    AssertEqual(r.Denominator(), 3, "denominator 2/3");
  }
  {
    Rational r(-2, -3);
    AssertEqual(r.Numerator(), 2, "numerator -2/-3");
    AssertEqual(r.Denominator(), 3, "denominator -2/-3");
  }
}

void TestNegative() {
  {
    Rational r(-2, 3);
    AssertEqual(r.Numerator(), -2, "numerator -2/3");
    AssertEqual(r.Denominator(), 3, "denominator -2/3");
  }
  {
    Rational r(2, -3);
    AssertEqual(r.Numerator(), -2, "numerator 2/-3");
    AssertEqual(r.Denominator(), 3, "denominator 2/-3");
  }
}

void TestCompact() {
  {
    Rational r(10, 5);
    AssertEqual(r.Numerator(), 2, "numerator 10/5");
    AssertEqual(r.Denominator(), 1, "denominator 10/5");
  }
  {
    Rational r(5, 10);
    AssertEqual(r.Numerator(), 1, "numerator 5/10");
    AssertEqual(r.Denominator(), 2, "denominator 5/10");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
  runner.RunTest(TestPositive, "TestPositive");
  runner.RunTest(TestNegative, "TestNegative");
  runner.RunTest(TestCompact, "TestCompact");

  return 0;
}
