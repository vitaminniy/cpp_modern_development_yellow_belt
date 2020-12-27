#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "test_runner.h"

static const std::string kIncognito = "Incognito";

class Person {
public:
  void ChangeFirstName(int year, const std::string &first_name) {
    first_names[year] = first_name;
  }

  void ChangeLastName(int year, const std::string &last_name) {
    last_names[year] = last_name;
  }

  std::string GetFullName(int year) {
    const auto first_name = find_by_year(first_names, year);
    const auto last_name = find_by_year(last_names, year);
    if (!first_name.has_value() && !last_name.has_value())
      return kIncognito;

    if (!first_name.has_value())
      return last_name.value() + " with unknown first name";

    if (!last_name.has_value())
      return first_name.value() + " with unknown last name";

    return first_name.value() + " " + last_name.value();
  }

private:
  std::map<int, std::string> first_names;
  std::map<int, std::string> last_names;

  const std::optional<std::string>
  find_by_year(const std::map<int, std::string> &m, int year) const {
    auto it =
        std::find_if(m.rbegin(), m.rend(), [&year = year](auto &p) -> bool {
          return year >= p.first;
        });
    return it != m.rend() ? std::make_optional(it->second) : std::nullopt;
  }
};

void TestIncognito() {
  {
    Person p;
    const auto fn = p.GetFullName(2020);
    AssertEqual(fn, kIncognito, "person with no bio is incognito");
  }
  {
    Person p;
    p.ChangeFirstName(2020, "A");
    p.ChangeLastName(2020, "B");

    const auto fn = p.GetFullName(2019);
    AssertEqual(fn, kIncognito, "person future bio is incognito");
  }
}

void TestPerson() {
  {
    Person p;
    p.ChangeFirstName(1996, "A");
    p.ChangeLastName(1996, "B");

    AssertEqual(p.GetFullName(2020), "A B", "1996: A B");
  }
  {
    Person p;
    p.ChangeFirstName(1996, "A");
    p.ChangeFirstName(1997, "C");
    p.ChangeLastName(1996, "B");

    AssertEqual(p.GetFullName(2020), "C B", "1996: A B; 1997: C B");
  }
  {
    Person p;
    p.ChangeFirstName(1996, "A");
    p.ChangeFirstName(1997, "C");
    p.ChangeLastName(1996, "B");
    p.ChangeLastName(1997, "D");

    AssertEqual(p.GetFullName(2020), "C D", "1996: A B; 1997: C D");
  }
  {
    Person p;
    p.ChangeFirstName(1994, "A");

    AssertEqual(p.GetFullName(1995), "A with unknown last name", "1994: A _");
  }
  {
    Person p;
    p.ChangeFirstName(1994, "A");
    p.ChangeFirstName(1995, "B");

    AssertEqual(p.GetFullName(1995), "B with unknown last name",
                "ask first 1995 -> 1994: A _; 1995: B _");
  }
  {
    Person p;
    p.ChangeLastName(1994, "A");
    p.ChangeLastName(1995, "B");

    AssertEqual(p.GetFullName(1995), "B with unknown first name",
                "ask last 1995 -> 1994: A _; 1995: B _");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito, "TestIncognito");
  runner.RunTest(TestPerson, "TestPerson");

  return 0;
}
