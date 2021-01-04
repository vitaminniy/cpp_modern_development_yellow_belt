#include <algorithm>
#include <set>
#include <vector>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T> &elements,
                                   const T &border) {
  auto it = find_if(elements.begin(), elements.end(),
                    [border](const T &e) -> bool { return e > border; });

  if (it == elements.end()) {
    return {};
  }

  std::vector<T> result;
  result.reserve(elements.size());

  while (it != elements.end()) {
    result.push_back(*it);
    it++;
  }

  return result;
}
