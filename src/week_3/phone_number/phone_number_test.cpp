#include <stdexcept>
#include <vector>

#include "phone_number.h"
#include "test_runner.h"

struct TestCase {
  std::string number;
  std::string country;
  std::string city;
  std::string local;
  bool throws;
};

std::vector<TestCase> test_cases = {
    {"+7-495-111-22-33", "7", "495", "111-22-33", false},
    {"+7-495-1112233", "7", "495", "1112233", false},
    {"+323-22-460002", "323", "22", "460002", false},
    {"1-2-333", "", "", "", true},
    {"+7-1233", "", "", "", true},
};

void RunPass(const TestCase &tc) {
  PhoneNumber number = PhoneNumber(tc.number);
  AssertEqual(number.GetCountryCode(), tc.country, "country code mismatch");
  AssertEqual(number.GetCityCode(), tc.city, "city code mismatch");
  AssertEqual(number.GetLocalNumber(), tc.local, "local number mismatch");
  AssertEqual(number.GetInternationalNumber(), tc.number,
              "international number mismatch");
}

void RunThrow(const TestCase &tc) {
  try {
    PhoneNumber(tc.number);
  } catch (const std::invalid_argument &) {
    return;
  }
  AssertFalse("expected exception but got nothing");
}

void RunTest(const TestCase &tc) {
  if (tc.throws) {
    RunThrow(tc);
    return;
  }
  RunPass(tc);
}

int main() {
  TestRunner runner;
  for (const auto &tc : test_cases) {
    const std::string msg = tc.throws ? "THROWS" : "VALID";
    runner.RunTest(RunTest, tc, msg + " " + tc.number);
  }
}
