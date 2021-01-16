#include "database.h"

#include <algorithm>
#include <sstream>
#include <utility>

void Database::Add(const Date &date, const std::string &event) {
  if (events_[date].unique.insert(event).second) {
    events_[date].events.push_back(event);
  }
}

void Database::Print(std::ostream &dst) const {
  for (const auto &[date, record] : events_) {
    for (const auto &event : record.events) {
      dst << date << ' ' << event << std::endl;
    }
  }
}

std::string Database::Last(const Date &date) const {
  auto it = events_.upper_bound(date);
  if (it == events_.cbegin()) {
    return "No entries";
  }

  it = std::prev(it);
  std::stringstream ss;
  ss << it->first << ' ' << it->second.events.back();
  return ss.str();
}

std::ostream &operator<<(std::ostream &dst, const Event &event) {
  dst << event.first << " " << event.second;
  return dst;
}
