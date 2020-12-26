#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using BusesToStops = std::map<std::string, std::vector<std::string>>;
using StopsToBuses = std::map<std::string, std::vector<std::string>>;

enum class QueryType { NewBus, BusesForStop, StopsForBus, AllBuses };

struct Query {
  QueryType type;
  std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

constexpr bool operator==(const Query &lhs, const Query &rhs) {
  return std::tie(lhs.type, lhs.bus, lhs.bus, lhs.stops) ==
         std::tie(rhs.type, rhs.bus, rhs.bus, rhs.stops);
}

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

struct BusesForStopResponse {
  std::vector<std::string> buses;
};

inline bool operator==(const BusesForStopResponse &lhs,
                       const BusesForStopResponse &rhs) {
  return lhs.buses == rhs.buses;
}

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

struct StopsForBusResponse {
  std::vector<std::string> stops;
  StopsToBuses stops_to_buses;
};

inline bool operator==(const StopsForBusResponse &lhs,
                       const StopsForBusResponse &rhs) {
  return std::tie(lhs.stops, lhs.stops_to_buses) ==
         std::tie(rhs.stops, rhs.stops_to_buses);
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

struct AllBusesResponse {
  BusesToStops buses;
};

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

class BusManager {
public:
  void AddBus(const std::string &bus, const std::vector<std::string> &stops) {
    buses_to_stops[bus] = stops;
    for (const auto &s : stops) {
      stops_to_buses[s].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const std::string &stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return {};
    }

    return {stops_to_buses.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const std::string &bus) const {
    if (buses_to_stops.count(bus) == 0) {
      return {};
    }

    StopsForBusResponse response;
    for (const auto &s : buses_to_stops.at(bus)) {
      auto buses = stops_to_buses.at(s);

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

  AllBusesResponse GetAllBuses() const { return {buses_to_stops}; }

  inline BusesToStops GetBusesForStops() const { return buses_to_stops; }
  inline StopsToBuses GetStopsToBuses() const { return stops_to_buses; }

private:
  BusesToStops buses_to_stops;
  StopsToBuses stops_to_buses;
};

void TestQueryParse();
void TestAddBus();
void TestBusesForStop();
void TestStopsForBus();
void TestAllBuses();

int main(int argc, char **argv) {
  if (argc > 1 && std::string(argv[1]) == "test") {
    TestQueryParse();
    TestAddBus();
    TestBusesForStop();
    TestStopsForBus();
    TestAllBuses();

    return 0;
  }

  int query_count;
  Query q;

  std::cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    std::cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      std::cout << bm.GetBusesForStop(q.stop) << std::endl;
      break;
    case QueryType::StopsForBus:
      std::cout << bm.GetStopsForBus(q.bus) << std::endl;
      break;
    case QueryType::AllBuses:
      std::cout << bm.GetAllBuses() << std::endl;
      break;
    }
  }

  return 0;
}

void TestQueryParse() {
  struct test_case {
    std::string name;
    std::string input;
    Query expected;
  };

  std::vector<test_case> cases = {
    {
      "NEW_BUS with several stops",
      "NEW_BUS 32K 3 School Library Pool",
      {QueryType::NewBus, "32K", "", {"School", "Library", "Pool"}},
    },
    {
      "simple NEW_BUS with single stop",
      "NEW_BUS 32 1 School",
      {QueryType::NewBus, "32", "", {"School"}},
    },
    {
      "simple BUSES_FOR_STOP School",
      "BUSES_FOR_STOP school",
      {QueryType::BusesForStop, "", "School", {}}
    },
    {
      "simple STOPS_FOR_BUS 32k",
      "STOPS_FOR_BUS 32k",
      {QueryType::StopsForBus, "32k", "", {}}
    },
    {
      "simple ALL BUSES",
      "ALL_BUSES",
      {QueryType::AllBuses, "", "", {}}
    },
  };

  for (const auto& c : cases) {
    std::stringstream ss(c.input);
    Query query;
    ss >> query;
    assert((c.expected == query) && c.name.c_str());
  }
}

void TestAddBus() {
  {
    BusManager bm;
    bm.AddBus("A59", {"School", "Library"});

    const BusesToStops buses = {{"A59", {"School", "Library"}}};
    const StopsToBuses stops = {{"School", {"A59"}}, {"Library", {"A59"}}};
    assert((buses == bm.GetBusesForStops()) && "Buses mismatch");
    assert((stops == bm.GetStopsToBuses()) && "Stops mismatch");
  }
}

void TestBusesForStop() {
  {
    BusManager empty;

    const BusesForStopResponse expected = {};
    const auto bfs = empty.GetBusesForStop("School");
    assert((expected == bfs) && "Expected empty managers to be equal");
  }
  {
    BusManager bm;
    bm.AddBus("A58", {"School"});
    bm.AddBus("A59", {"School"});
    bm.AddBus("A60", {"School"});

    const BusesForStopResponse expected = {};
    const auto response = bm.GetBusesForStop("Library");
    assert((expected == response) && "missing: Expected Library has no buses");
  }
  {
    BusManager bm;
    bm.AddBus("A58", {"School"});
    bm.AddBus("A59", {"School"});
    bm.AddBus("A60", {"School"});

    const auto bfs = bm.GetBusesForStop("School");
    const BusesForStopResponse expected = {{"A58", "A59", "A60"}};
    assert((expected == bfs) && "Happy path failed");
  }
  {
    BusManager bm;
    bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});
    bm.AddBus("32K", {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino",
        "Solntsevo", "Skolkovo"});

    const BusesForStopResponse response = bm.GetBusesForStop("Vnukovo");
    const BusesForStopResponse expected = {{"32", "32K"}};
    assert(response == expected);
  }
}

void TestStopsForBus() {
  {
    BusManager bm;

    const StopsForBusResponse response = bm.GetStopsForBus("A59");
    const StopsForBusResponse expected = {};
    assert((expected == response) && "Expected empty response");
  }
  {
    BusManager bm;
    bm.AddBus("A59", {"School"});

    const StopsForBusResponse response = bm.GetStopsForBus("A60");
    const StopsForBusResponse expected = {};
    assert((expected == response) && "Expected empty response for missing bus");
  }
  {
    BusManager bm;
    bm.AddBus("A59", {"School"});

    const StopsForBusResponse response = bm.GetStopsForBus("A59");
    const StopsForBusResponse expected = {{"School"},{{"School", {}}}};
    assert((expected == response) && "Expected no interchanges");
  }
  {
    BusManager bm;
    bm.AddBus("A59", {"School"});
    bm.AddBus("A60", {"School"});
    bm.AddBus("A61", {"School"});

    const StopsForBusResponse response = bm.GetStopsForBus("A60");
    const StopsForBusResponse expected = {
      {"School"},
      {{"School", {"A59", "A61"}}}
    };
    assert((expected == response) && "Expected interchanges to exist");
  }
  {
    BusManager bm;
    bm.AddBus("32", {"Tolstopaltsevo", "Marushkino", "Vnukovo"});
    bm.AddBus("32K", {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino",
        "Solntsevo", "Skolkovo"});
    bm.AddBus("950", {"Kokoshkino", "Marushkino", "Vnukovo", "Peredelkino", 
        "Solntsevo", "Troparyovo"});
    bm.AddBus("272", {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"});

    const StopsForBusResponse response = bm.GetStopsForBus("272");
    const StopsForBusResponse expected = {
      {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"},
      {
        {"Vnukovo", {"32", "32K", "950"}},
        {"Moskovsky", {}},
        {"Rumyantsevo", {}},
        {"Troparyovo", {"950"}}
      }
    };
    std::cout << "Got\n" << response << std::endl;
    std::cout << "Want\n" << expected << std::endl;

    assert(response == expected);
  }
}

void TestAllBuses() {}
