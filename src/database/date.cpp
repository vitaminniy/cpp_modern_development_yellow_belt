#include "date.h"

#include <iomanip>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <tuple>

namespace {

std::tuple<int, int, int> tie(const Date &date) {
  return std::make_tuple(date.GetYear(), date.GetMonth(), date.GetDay());
}

} // namespace

Date ParseDate(std::istream &src) {
  src >> std::ws;

  bool ok = true;

  int year;
  ok = ok && (src >> year);
  ok = ok && (src.peek() == '-');
  src.ignore(1);

  int month;
  ok = ok && (src >> month);
  ok = ok && (src.peek() == '-');
  src.ignore(1);

  int day;
  ok = ok && (src >> day);

  if (!ok) {
    throw std::logic_error("Wrong date format");
  }

  return Date(year, month, day);
}

Date::Date(int year, int month, int day) {
  if (month < 1 || month > 12)
    throw std::logic_error("Month value is invalid: " + std::to_string(month));

  if (day < 1 || day > 31)
    throw std::logic_error("Day value is invalid: " + std::to_string(day));

  year_ = year;
  month_ = month;
  day_ = day;
}

bool operator==(const Date &lhs, const Date &rhs) {
  return tie(lhs) == tie(rhs);
}

bool operator!=(const Date &lhs, const Date &rhs) {
  return tie(lhs) != tie(rhs);
}

bool operator<(const Date &lhs, const Date &rhs) { return tie(lhs) < tie(rhs); }

bool operator<=(const Date &lhs, const Date &rhs) {
  return tie(lhs) <= tie(rhs);
}

bool operator>(const Date &lhs, const Date &rhs) { return tie(lhs) > tie(rhs); }

bool operator>=(const Date &lhs, const Date &rhs) {
  return tie(lhs) >= tie(rhs);
}

std::ostream &operator<<(std::ostream &dst, const Date &d) {
  dst << std::setw(4) << std::setfill('0') << d.GetYear() << "-" << std::setw(2)
      << std::setfill('0') << d.GetMonth() << "-" << std::setw(2)
      << std::setfill('0') << d.GetDay();
  return dst;
}
