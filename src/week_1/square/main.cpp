#include <map>
#include <utility>
#include <vector>

template <typename T> std::vector<T> Sqr(std::vector<T> v);

template <typename Key, typename Value>
std::map<Key, Value> Sqr(std::map<Key, Value> m);

template <typename First, typename Second>
std::pair<First, Second> Sqr(std::pair<First, Second> p);

template <typename T> constexpr inline T Sqr(T t) { return t * t; }

template <typename T> std::vector<T> Sqr(std::vector<T> v) {
  for (auto &i : v) {
    i = Sqr(i);
  }
  return v;
}

template <typename First, typename Second>
std::pair<First, Second> Sqr(std::pair<First, Second> p) {
  return std::make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename Key, typename Value>
std::map<Key, Value> Sqr(std::map<Key, Value> m) {
  for (auto &[k, v] : m) {
    v = Sqr(v);
  }
  return m;
}
