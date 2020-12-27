#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_runner.h"

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
