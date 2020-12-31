#include "query.h"

std::istream &operator>>(std::istream &is, Query &q) {
  std::string type;
  is >> type;

  if (type == "NEW_BUS") {
    size_t stop_count;
    std::string bus;

    q.type = QueryType::NewBus;
    is >> bus >> stop_count;

    std::vector<std::string> stops(stop_count);
    for (size_t i = 0; i < stops.size(); i++) {
      is >> stops[i];
    }

    q.type = QueryType::NewBus;
    q.bus = bus;
    q.stops = stops;
  } else if (type == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (type == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (type == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }
  return is;
}
