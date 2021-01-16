#pragma once

#include <istream>
#include <ostream>

class Date;

Date ParseDate(std::istream &src);

class Date {
public:
  Date() = default;
  Date(int year, int month, int day);

  inline int GetYear() const { return year_; }
  inline int GetMonth() const { return month_; }
  inline int GetDay() const { return day_; }

private:
  int year_{};
  int month_{};
  int day_{};
};

bool operator==(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);

std::ostream &operator<<(std::ostream &dst, const Date &d);
