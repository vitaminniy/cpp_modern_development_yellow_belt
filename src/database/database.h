#pragma once

#include "date.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <ostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using Event = std::pair<Date, std::string>;

struct Record {
  std::unordered_set<std::string> unique;
  std::vector<std::string> events;
};

class Database {
public:
  Database() = default;

  void Add(const Date &date, const std::string &event);
  void Print(std::ostream &dst) const;
  std::string Last(const Date &date) const;

  template <typename Predicate>
  std::vector<Event> FindIf(Predicate &&predicate) const {
    std::vector<Event> result;
    for (const auto &[date, events] : events_) {
      for (const auto &event : events.events) {
        if (predicate(date, event)) {
          result.push_back({date, event});
        }
      }
    }
    return result;
  }

  template <typename Predicate> int RemoveIf(Predicate &&predicate) {
    int result = 0;
    std::map<Date, Record> events;
    for (auto &[date, record] : events_) {
      auto it = std::stable_partition(
          record.events.begin(), record.events.end(),
          [&predicate, &date_ = date](const auto &event) -> bool {
            return predicate(date_, event);
          });

      if (it == record.events.end()) {
        result += record.events.size();
        continue;
      }

      Record r;
      r.events = std::vector<std::string>(it, record.events.end());
      r.unique =
          std::unordered_set<std::string>(r.events.cbegin(), r.events.cend());

      result += record.events.size() - r.events.size();
      events[date] = r;
    }

    events_ = events;
    return result;
  }

private:
  std::map<Date, Record> events_;
};

std::ostream &operator<<(std::ostream &dst, const Event &event);
