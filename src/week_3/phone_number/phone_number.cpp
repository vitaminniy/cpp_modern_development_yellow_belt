#include <sstream>
#include <stdexcept>
#include <string>

#include "phone_number.h"

PhoneNumber::PhoneNumber(const std::string &number) {
  if (number.empty()) {
    throw std::invalid_argument("number is empty");
  }

  std::stringstream ss(number);
  if (char c = ss.get(); c != '+') {
    throw std::invalid_argument("number does not have '+'");
  }

  std::getline(ss, country_code_, '-');
  if (country_code_.empty() || country_code_.size() > 3) {
    throw std::invalid_argument("invalid country code: " + country_code_);
  }

  std::getline(ss, city_code_, '-');
  if (city_code_.empty() || city_code_.size() > 3) {
    throw std::invalid_argument("invalid city code: " + city_code_);
  }

  std::getline(ss, local_number_);
  if (local_number_.empty()) {
    throw std::invalid_argument("empty local number");
  }
}

std::string PhoneNumber::GetCountryCode() const { return country_code_; }
std::string PhoneNumber::GetCityCode() const { return city_code_; }
std::string PhoneNumber::GetLocalNumber() const { return local_number_; }
std::string PhoneNumber::GetInternationalNumber() const {
  return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
