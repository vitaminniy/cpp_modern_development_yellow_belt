#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "test_runner.h"

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
