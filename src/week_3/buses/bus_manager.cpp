#include "bus_manager.h"

void BusManager::AddBus(const std::string &bus,
                        const std::vector<std::string> &stops) {
  buses_to_stops[bus] = stops;
  for (const auto &s : stops) {
    stops_to_buses[s].push_back(bus);
  }
}

BusesForStopResponse
BusManager::GetBusesForStop(const std::string &stop) const {
  if (stops_to_buses.count(stop) == 0) {
    return {};
  }

  return {stops_to_buses.at(stop)};
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string &bus) const {
  if (buses_to_stops.count(bus) == 0) {
    return {};
  }

  StopsForBusResponse response;
  for (const auto &s : buses_to_stops.at(bus)) {
    const auto buses = stops_to_buses.at(s);

    response.stops.push_back(s);
    response.stops_to_buses[s].reserve(buses.size());

    if (buses.size() == 1) {
      continue;
    }

    for (const auto &b : buses) {
      if (b == bus)
        continue;

      response.stops_to_buses[s].push_back(b);
    }
  }

  return response;
}

AllBusesResponse BusManager::GetAllBuses() const { return {buses_to_stops}; }

std::map<std::string, std::vector<std::string>>
BusManager::GetBusesForStops() const {
  return buses_to_stops;
}

std::map<std::string, std::vector<std::string>>
BusManager::GetStopsToBuses() const {
  return stops_to_buses;
}
