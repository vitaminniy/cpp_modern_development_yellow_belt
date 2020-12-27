#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_runner.h"

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
