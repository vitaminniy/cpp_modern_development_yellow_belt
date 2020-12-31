#include "responses.h"

std::ostream &operator<<(std::ostream &os, const BusesForStopResponse &r) {
  if (r.buses.empty()) {
    os << "No stop";
    return os;
  }

  for (size_t i = 0; i < r.buses.size(); i++) {
    if (i > 0)
      os << " ";
    os << r.buses[i];
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, const StopsForBusResponse &r) {
  if (r.stops.empty()) {
    os << "No bus";
    return os;
  }

  std::string stop;
  for (size_t i = 0; i < r.stops.size(); i++) {
    stop = r.stops[i];
    if (i > 0)
      os << std::endl;

    os << "Stop " << stop << ": ";
    const auto buses = r.stops_to_buses.at(stop);
    if (buses.empty()) {
      os << "no interchange";
      continue;
    }

    for (size_t j = 0; j < buses.size(); j++) {
      if (j > 0)
        os << " ";
      os << buses[j];
    }
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, const AllBusesResponse &r) {
  if (r.buses.empty()) {
    os << "No buses";
    return os;
  }

  for (const auto &[b, stops] : r.buses) {
    os << "Bus " << b << ": ";
    for (const auto &s : stops) {
      os << s << " ";
    }
    os << std::endl;
  }

  return os;
}
