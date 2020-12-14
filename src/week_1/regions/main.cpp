#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

enum class Lang { DE, FR, IT };

struct Region {
  std::string std_name;
  std::string parent_std_name;
  std::map<Lang, std::string> names;
  int64_t population;
};

bool operator<(const Region &lhs, const Region &rhs) {
  return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names,
                  lhs.population) <
         std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

// Returns maximum number of copies.
// NOTE(vitaminniy): naive approach
int FindMaxRepetitionCount(const std::vector<Region> &regions) {
  if (regions.empty())
    return 0;

  int result = 0;
  std::map<Region, int> seen;
  for (const auto &r : regions) {
    seen[r]++;
    result = std::max(result, seen[r]);
  }

  return result;
}

int main() {
  std::cout
      << FindMaxRepetitionCount({
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
         })
      << std::endl;

  std::cout
      << FindMaxRepetitionCount({
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Russia",
              "Eurasia",
              {{Lang::DE, "Russland"},
               {Lang::FR, "Russie"},
               {Lang::IT, "Russia"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"},
               {Lang::FR, "Moscou deux"},
               {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Toulouse",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              89},
             {"Moscow",
              "Russia",
              {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
              31},
         })
      << std::endl;

  return 0;
}
